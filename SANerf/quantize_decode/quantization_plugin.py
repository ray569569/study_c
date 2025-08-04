"""
SANeRF-HQ 量化外挂模块
用法：将此文件保存为 quantization_plugin.py，然后在您的项目中导入使用
"""

import torch
import numpy as np
import cv2
import os
import json
import matplotlib.pyplot as plt
from skimage.metrics import structural_similarity as ssim
from skimage.metrics import peak_signal_noise_ratio as psnr
from typing import Dict, List, Tuple, Any, Union, Optional
import glob
from pathlib import Path


class QuantizationPlugin:
    """轻量级量化外挂，可插入任何函数"""
    
    def __init__(self, precision_type: str = "FP32", int_bits: int = 4, frac_bits: int = 12, enabled: bool = True):
        """
        Args:
            precision_type: 'FP32', 'FP16', 'Q4.12' 等
            int_bits: 整数位数
            frac_bits: 小数位数  
            enabled: 是否启用量化（用于对照组）
        """
        self.precision_type = precision_type
        self.int_bits = int_bits
        self.frac_bits = frac_bits
        self.enabled = enabled
        self.quantize_count = 0
        
    def __call__(self, data: Union[torch.Tensor, np.ndarray]) -> Union[torch.Tensor, np.ndarray]:
        """外挂主函数 - 直接替换原始数据"""
        if not self.enabled:
            return data  # 对照组：不做任何处理
        
        self.quantize_count += 1
        return self._quantize_data(data)
    
    def _quantize_data(self, data: Union[torch.Tensor, np.ndarray]) -> Union[torch.Tensor, np.ndarray]:
        """执行量化"""
        is_numpy = isinstance(data, np.ndarray)
        original_device = None
        
        # 转换为torch tensor
        if is_numpy:
            tensor = torch.from_numpy(data)
        else:
            tensor = data
            original_device = tensor.device
            
        # 执行量化
        if self.precision_type == 'FP32':
            quantized = tensor.float()
        elif self.precision_type == 'FP16':
            quantized = tensor.half().float()
        elif self.precision_type.startswith('Q'):
            quantized = self._fixed_point_quantize(tensor)
        else:
            quantized = tensor
        
        # 恢复原始格式
        if is_numpy:
            return quantized.numpy()
        else:
            if original_device is not None:
                quantized = quantized.to(original_device)
            return quantized
    
    def _fixed_point_quantize(self, tensor: torch.Tensor) -> torch.Tensor:
        """固定点量化"""
        scale = 2 ** self.frac_bits
        max_val = 2 ** (self.int_bits + self.frac_bits - 1) - 1
        min_val = -2 ** (self.int_bits + self.frac_bits - 1)
        
        quantized = torch.round(tensor * scale)
        quantized = torch.clamp(quantized, min_val, max_val)
        
        return quantized / scale

class ResultCollector:
    """结果收集器，适配train.py的输出结构"""
    
    def __init__(self, base_dir: str = "./quantization_experiments"):
        self.base_dir = Path(base_dir)
        self.base_dir.mkdir(exist_ok=True)
        self.experiments = {}
        self.current_experiment = None
        
    def start_experiment(self, experiment_name: str):
        """开始一个新实验，创建目录"""
        self.current_experiment = experiment_name
        exp_dir = self.base_dir / experiment_name
        exp_dir.mkdir(exist_ok=True)
        
        self.experiments[experiment_name] = {
            'dir': exp_dir,
            'files': []
        }
        
        print(f"Started experiment: {experiment_name}")
        print(f"Results will be saved to: {exp_dir}")
        return exp_dir
    
    def collect_from_trainer_output(self, save_path: str, experiment_name: str = None):
        """
        从trainer的test()函数输出目录收集结果
        
        Args:
            save_path: trainer.test()的save_path目录
            experiment_name: 实验名称，如果为None则使用current_experiment
        """
        if experiment_name is None:
            experiment_name = self.current_experiment
            
        if experiment_name is None:
            raise ValueError("No experiment name provided and no current experiment set")
        
        source_dir = Path(save_path)
        if not source_dir.exists():
            raise ValueError(f"Source directory does not exist: {save_path}")
        
        # 创建实验目录
        exp_dir = self.base_dir / experiment_name
        exp_dir.mkdir(exist_ok=True)
        
        copied_files = []
        
        # 收集所有PNG图像文件
        for png_file in source_dir.glob("*.png"):
            if any(keyword in png_file.name.lower() for keyword in ['rgb', 'mask', 'depth']):
                dest_file = exp_dir / png_file.name
                import shutil
                shutil.copy2(png_file, dest_file)
                copied_files.append(dest_file)
        
        # 收集所有NPY数据文件  
        for npy_file in source_dir.glob("*.npy"):
            dest_file = exp_dir / npy_file.name
            import shutil
            shutil.copy2(npy_file, dest_file)
            copied_files.append(dest_file)
        
        # 记录实验
        self.experiments[experiment_name] = {
            'dir': exp_dir,
            'files': copied_files,
            'source_dir': source_dir
        }
        
        print(f"Collected {len(copied_files)} files for experiment: {experiment_name}")
        print(f"Files copied from: {source_dir}")
        print(f"Files saved to: {exp_dir}")
        return exp_dir
    
    def auto_collect_from_default_path(self, workspace: str, experiment_name: str):
        """
        自动从默认的results路径收集结果
        
        Args:
            workspace: 模型的workspace路径 (通常是 ./workspace/model_name)
            experiment_name: 实验名称
        """
        # SANeRF默认结果路径
        default_results_path = Path(workspace) / "results"
        
        if default_results_path.exists():
            return self.collect_from_trainer_output(str(default_results_path), experiment_name)
        else:
            print(f"Warning: Default results path not found: {default_results_path}")
            return None
    
    def compare_experiments(self, baseline_name: str, target_names: List[str]) -> Dict[str, Dict[str, float]]:
        """
        比较实验结果
        
        Args:
            baseline_name: 基准实验名称（通常是FP32_original）
            target_names: 要比较的实验名称列表
        
        Returns:
            比较结果字典
        """
        if baseline_name not in self.experiments:
            raise ValueError(f"Baseline experiment '{baseline_name}' not found")
        
        baseline_dir = self.experiments[baseline_name]['dir']
        comparison_results = {}
        
        for target_name in target_names:
            if target_name not in self.experiments:
                print(f"Warning: Experiment '{target_name}' not found, skipping...")
                continue
                
            target_dir = self.experiments[target_name]['dir']
            metrics = self._calculate_metrics(baseline_dir, target_dir)
            comparison_results[target_name] = metrics
            
            # 保存比较结果
            result_file = self.base_dir / f"comparison_{baseline_name}_vs_{target_name}.json"
            with open(result_file, 'w') as f:
                json.dump(metrics, f, indent=2)
        
        return comparison_results
    
    def _calculate_metrics(self, baseline_dir: Path, target_dir: Path) -> Dict[str, float]:
        """计算两个实验目录之间的指标"""
        metrics = {
            'image_psnr': [], 'image_ssim': [], 'image_mse': [],
            'mask_iou': [], 'mask_dice': [],
            'depth_mse': [], 'depth_mae': []
        }
        
        # 比较图像
        baseline_images = sorted(baseline_dir.glob("*rgb*.png")) + sorted(baseline_dir.glob("*image*.png"))
        target_images = sorted(target_dir.glob("*rgb*.png")) + sorted(target_dir.glob("*image*.png"))
        
        for baseline_img, target_img in zip(baseline_images, target_images):
            try:
                # 读取图像
                baseline_data = cv2.imread(str(baseline_img))
                target_data = cv2.imread(str(target_img))
                
                if baseline_data is not None and target_data is not None:
                    baseline_data = cv2.cvtColor(baseline_data, cv2.COLOR_BGR2RGB).astype(np.float32) / 255.0
                    target_data = cv2.cvtColor(target_data, cv2.COLOR_BGR2RGB).astype(np.float32) / 255.0
                    
                    # 计算指标
                    img_psnr = psnr(baseline_data, target_data, data_range=1.0)
                    img_ssim = ssim(baseline_data, target_data, multichannel=True, channel_axis=-1, data_range=1.0)
                    img_mse = np.mean((baseline_data - target_data) ** 2)
                    
                    metrics['image_psnr'].append(img_psnr)
                    metrics['image_ssim'].append(img_ssim)
                    metrics['image_mse'].append(img_mse)
            except Exception as e:
                print(f"Error processing images {baseline_img} vs {target_img}: {e}")
        
        # 比较mask和depth（npy文件）
        for data_type in ['mask', 'depth']:
            baseline_files = sorted(baseline_dir.glob(f"*{data_type}*.npy"))
            target_files = sorted(target_dir.glob(f"*{data_type}*.npy"))
            
            for baseline_file, target_file in zip(baseline_files, target_files):
                try:
                    baseline_data = np.load(baseline_file)
                    target_data = np.load(target_file)
                    
                    if data_type == 'mask':
                        # 计算mask指标
                        baseline_binary = (baseline_data > 0.5).astype(np.float32)
                        target_binary = (target_data > 0.5).astype(np.float32)
                        
                        intersection = np.sum(baseline_binary * target_binary)
                        union = np.sum(baseline_binary) + np.sum(target_binary) - intersection
                        iou = intersection / (union + 1e-8)
                        dice = (2 * intersection) / (np.sum(baseline_binary) + np.sum(target_binary) + 1e-8)
                        
                        metrics['mask_iou'].append(iou)
                        metrics['mask_dice'].append(dice)
                        
                    elif data_type == 'depth':
                        # 计算depth指标
                        mse = np.mean((baseline_data - target_data) ** 2)
                        mae = np.mean(np.abs(baseline_data - target_data))
                        
                        metrics['depth_mse'].append(mse)
                        metrics['depth_mae'].append(mae)
                        
                except Exception as e:
                    print(f"Error processing {data_type} files {baseline_file} vs {target_file}: {e}")
        
        # 计算平均值
        avg_metrics = {}
        for key, values in metrics.items():
            if values:
                avg_metrics[key] = float(np.mean(values))
                avg_metrics[f'{key}_std'] = float(np.std(values))
            else:
                avg_metrics[key] = 0.0
                avg_metrics[f'{key}_std'] = 0.0
        
        return avg_metrics
    
    def plot_comparison_results(self, comparison_results: Dict[str, Dict[str, float]], 
                              save_path: Optional[str] = None):
        """绘制比较结果图表"""
        
        experiment_names = list(comparison_results.keys())
        psnr_values = [comparison_results[name]['image_psnr'] for name in experiment_names]
        ssim_values = [comparison_results[name]['image_ssim'] for name in experiment_names]
        
        # 提取位宽信息用于排序
        def extract_bit_width(name):
            if 'Q' in name:
                parts = name.split('_')[0].replace('Q', '').split('.')
                if len(parts) == 2:
                    return int(parts[0]) + int(parts[1])
            elif 'FP16' in name:
                return 16
            elif 'FP32' in name:
                return 32
            return 16  # 默认值
        
        # 按位宽排序
        sorted_data = sorted(zip(experiment_names, psnr_values, ssim_values), 
                           key=lambda x: extract_bit_width(x[0]))
        experiment_names, psnr_values, ssim_values = zip(*sorted_data)
        bit_widths = [extract_bit_width(name) for name in experiment_names]
        
        # 创建图表
        fig, axes = plt.subplots(2, 2, figsize=(15, 12))
        fig.suptitle('Quantization Impact Analysis', fontsize=16)
        
        # PSNR vs 实验配置
        axes[0,0].bar(range(len(experiment_names)), psnr_values, color='skyblue')
        axes[0,0].set_xlabel('Experiment Configuration')
        axes[0,0].set_ylabel('PSNR (dB)')
        axes[0,0].set_title('PSNR by Configuration')
        axes[0,0].set_xticks(range(len(experiment_names)))
        axes[0,0].set_xticklabels(experiment_names, rotation=45, ha='right')
        axes[0,0].grid(True, alpha=0.3)
        
        # 添加PSNR阈值线
        axes[0,0].axhline(y=30, color='red', linestyle='--', alpha=0.7, label='Good Quality (30dB)')
        axes[0,0].axhline(y=25, color='orange', linestyle='--', alpha=0.7, label='Acceptable (25dB)')
        axes[0,0].legend()
        
        # SSIM vs 实验配置
        axes[0,1].bar(range(len(experiment_names)), ssim_values, color='lightgreen')
        axes[0,1].set_xlabel('Experiment Configuration')
        axes[0,1].set_ylabel('SSIM')
        axes[0,1].set_title('SSIM by Configuration')
        axes[0,1].set_xticks(range(len(experiment_names)))
        axes[0,1].set_xticklabels(experiment_names, rotation=45, ha='right')
        axes[0,1].grid(True, alpha=0.3)
        
        # 添加SSIM阈值线
        axes[0,1].axhline(y=0.9, color='red', linestyle='--', alpha=0.7, label='Excellent (0.9)')
        axes[0,1].axhline(y=0.8, color='orange', linestyle='--', alpha=0.7, label='Good (0.8)')
        axes[0,1].legend()
        
        # PSNR vs 位宽
        axes[1,0].plot(bit_widths, psnr_values, 'bo-', linewidth=2, markersize=8)
        axes[1,0].set_xlabel('Bit Width')
        axes[1,0].set_ylabel('PSNR (dB)')
        axes[1,0].set_title('PSNR vs Bit Width')
        axes[1,0].grid(True, alpha=0.3)
        
        # 标记急剧下降点
        for i in range(1, len(psnr_values)):
            if psnr_values[i-1] - psnr_values[i] > 2:  # PSNR下降超过2dB
                axes[1,0].annotate('Sharp Drop', 
                                 xy=(bit_widths[i], psnr_values[i]),
                                 xytext=(bit_widths[i]+1, psnr_values[i]+2),
                                 arrowprops=dict(arrowstyle='->', color='red'),
                                 color='red', fontweight='bold')
        
        # SSIM vs 位宽
        axes[1,1].plot(bit_widths, ssim_values, 'go-', linewidth=2, markersize=8)
        axes[1,1].set_xlabel('Bit Width')
        axes[1,1].set_ylabel('SSIM')
        axes[1,1].set_title('SSIM vs Bit Width')
        axes[1,1].grid(True, alpha=0.3)
        
        plt.tight_layout()
        
        if save_path:
            plt.savefig(save_path, dpi=300, bbox_inches='tight')
            print(f"Analysis plot saved to: {save_path}")
        
        plt.show()
        
        # 找到最佳配置
        self._find_optimal_config(comparison_results)
    
    def _find_optimal_config(self, comparison_results: Dict[str, Dict[str, float]]):
        """找到最佳量化配置"""
        print("\n" + "="*50)
        print("OPTIMAL CONFIGURATION ANALYSIS")
        print("="*50)
        
        # 设定品质阈值
        min_psnr = 25.0  # 最低可接受PSNR
        min_ssim = 0.8   # 最低可接受SSIM
        
        candidates = []
        for name, metrics in comparison_results.items():
            if metrics['image_psnr'] >= min_psnr and metrics['image_ssim'] >= min_ssim:
                candidates.append((name, metrics))
        
        if candidates:
            # 按位宽排序，找到最低位宽的配置
            def extract_bit_width(name):
                if 'Q' in name:
                    parts = name.split('_')[0].replace('Q', '').split('.')
                    if len(parts) == 2:
                        return int(parts[0]) + int(parts[1])
                elif 'FP16' in name:
                    return 16
                elif 'FP32' in name:
                    return 32
                return 16
            
            optimal = min(candidates, key=lambda x: extract_bit_width(x[0]))
            
            print(f"Optimal Configuration: {optimal[0]}")
            print(f"PSNR: {optimal[1]['image_psnr']:.2f} dB")
            print(f"SSIM: {optimal[1]['image_ssim']:.4f}")
            print(f"Bit Width: {extract_bit_width(optimal[0])}")
        else:
            print("No configuration meets the minimum quality requirements!")
            print("Consider relaxing the quality thresholds or using higher precision.")

class ExperimentManager:
    """实验管理器，简化批量实验流程"""
    
    def __init__(self, base_dir: str = "./quantization_experiments"):
        self.collector = ResultCollector(base_dir)
        self.quantization_configs = []
        
    def add_quantization_config(self, name: str, precision_type: str, 
                              int_bits: int = 4, frac_bits: int = 12):
        """添加量化配置"""
        self.quantization_configs.append({
            'name': name,
            'precision_type': precision_type,
            'int_bits': int_bits,
            'frac_bits': frac_bits
        })
        
    def create_quantizer(self, config_name: str) -> QuantizationPlugin:
        """根据配置名称创建量化器"""
        config = next((c for c in self.quantization_configs if c['name'] == config_name), None)
        if config is None:
            raise ValueError(f"Configuration '{config_name}' not found")
        
        return QuantizationPlugin(
            precision_type=config['precision_type'],
            int_bits=config['int_bits'],
            frac_bits=config['frac_bits'],
            enabled=True
        )
    
    def create_control_group(self) -> QuantizationPlugin:
        """创建对照组（不量化）"""
        return QuantizationPlugin(enabled=False)
    
    def run_batch_analysis(self, baseline_name: str = "FP32_baseline"):
        """运行批量分析"""
        experiment_names = [config['name'] for config in self.quantization_configs if config['name'] != baseline_name]
        comparison_results = self.collector.compare_experiments(baseline_name, experiment_names)
        
        # 绘制结果
        plot_path = self.collector.base_dir / "quantization_analysis.png"
        self.collector.plot_comparison_results(comparison_results, str(plot_path))
        
        return comparison_results

# 全局量化器变量（可选）
current_quantizer = None

def set_global_quantizer(quantizer: QuantizationPlugin):
    """设置全局量化器"""
    global current_quantizer
    current_quantizer = quantizer

def get_global_quantizer() -> QuantizationPlugin:
    """获取全局量化器"""
    global current_quantizer
    if current_quantizer is None:
        # 默认创建一个不量化的对照组
        current_quantizer = QuantizationPlugin(enabled=False)
    return current_quantizer

# 便捷函数
def quantize_if_enabled(data):
    """便捷的量化函数，使用全局量化器"""
    return get_global_quantizer()(data)

if __name__ == "__main__":
    print("Quantization Plugin loaded successfully!")
    print("Usage: from quantization_plugin import QuantizationPlugin, ExperimentManager")