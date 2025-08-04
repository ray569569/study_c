#!/usr/bin/env python3
"""
自動化量化結果分析腳本
自動掃描所有量化實驗結果並生成比較分析
"""

import os
import glob
from pathlib import Path
from quantization_plugin import ResultCollector

class AutoQuantizationAnalyzer:
    def __init__(self, base_workspace="/home/ray/SANeRF-HQ/workspace/quantization_test"):
        self.base_workspace = Path(base_workspace)
        self.collector = ResultCollector()
        self.baseline_name = "FP32_baseline"
        
    def scan_available_experiments(self):
        """自動掃描所有可用的實驗結果"""
        print("🔍 掃描可用的實驗結果...")
        
        available_experiments = []
        
        # 掃描workspace下的所有子目錄
        for exp_dir in self.base_workspace.iterdir():
            if exp_dir.is_dir():
                results_dir = exp_dir / "object_masks"
                if results_dir.exists():
                    # 檢查是否有PNG或NPY文件
                    has_files = (
                        list(results_dir.glob("*.png")) or 
                        list(results_dir.glob("*.npy")) 
                    )
                    if has_files:
                        available_experiments.append(exp_dir.name)
        
        # 排序實驗名稱
        available_experiments.sort()
        
        print(f"✅ 找到 {len(available_experiments)} 個實驗:")
        for i, exp in enumerate(available_experiments, 1):
            print(f"  {i:2d}. {exp}")
        
        return available_experiments
    
    def collect_all_experiments(self, experiment_names=None):
        """收集所有實驗結果"""
        if experiment_names is None:
            experiment_names = self.scan_available_experiments()
        
        print(f"\n📥 收集實驗結果...")
        
        collected = []
        failed = []
        
        for exp_name in experiment_names:
            try:
                results_path = self.base_workspace / exp_name / "object_masks"
                if results_path.exists():
                    self.collector.collect_from_trainer_output(str(results_path), exp_name)
                    collected.append(exp_name)
                    print(f"  ✅ {exp_name}")
                else:
                    print(f"  ❌ {exp_name} (結果目錄不存在)")
                    failed.append(exp_name)
            except Exception as e:
                print(f"  💥 {exp_name} (錯誤: {e})")
                failed.append(exp_name)
        
        print(f"\n📊 收集完成: {len(collected)} 成功, {len(failed)} 失敗")
        return collected, failed
    
    def filter_experiments_by_pattern(self, experiment_names, patterns):
        """根據模式過濾實驗"""
        filtered = []
        for exp in experiment_names:
            for pattern in patterns:
                if pattern in exp:
                    filtered.append(exp)
                    break
        return filtered
    
    def group_experiments_by_type(self, experiment_names):
        """按類型分組實驗"""
        groups = {
            'Q1.x': [],
            'Q2.x': [],
            'Q3.x': [],
            'Q4.x': [],
            'Q5.x': [],
            'Q6.x': [],
            'Q7.x': [],
            'Q8.x': [],
            'Q9.x': [],
            'Q10.x': [],
            'Q11.x': [],
            'Q12.x': [],
            'FP16': [],
            'Other': []
        }
        
        for exp in experiment_names:
            if exp == self.baseline_name:
                continue
                
            grouped = False
            for key in groups.keys():
                if key == 'FP16' and 'FP16' in exp:
                    groups[key].append(exp)
                    grouped = True
                    break
                elif key.startswith('Q') and exp.startswith(key.replace('.x', '.')):
                    groups[key].append(exp)
                    grouped = True
                    break
            
            if not grouped:
                groups['Other'].append(exp)
        
        # 移除空組
        groups = {k: v for k, v in groups.items() if v}
        return groups
    
    def run_comprehensive_analysis(self):
        """運行全面分析"""
        print("🚀 開始全面量化分析...")
        
        # 1. 掃描和收集所有實驗
        available_experiments = self.scan_available_experiments()
        collected, failed = self.collect_all_experiments(available_experiments)
        
        if self.baseline_name not in collected:
            print(f"❌ 基準實驗 {self.baseline_name} 未找到！")
            return
        
        # 2. 移除基準實驗，獲取比較目標
        target_experiments = [exp for exp in collected if exp != self.baseline_name]
        
        if not target_experiments:
            print("❌ 沒有找到量化實驗進行比較！")
            return
        
        print(f"\n🎯 將比較 {len(target_experiments)} 個量化實驗 vs {self.baseline_name}")
        
        # 3. 分組顯示
        groups = self.group_experiments_by_type(target_experiments)
        print(f"\n📋 實驗分組:")
        for group_name, experiments in groups.items():
            if experiments:
                print(f"  {group_name}: {experiments}")
        
        # 4. 執行比較分析
        print(f"\n⚖️  執行比較分析...")
        comparison = self.collector.compare_experiments(self.baseline_name, target_experiments)
        
        # 5. 生成圖表
        print(f"\n📈 生成分析圖表...")
        self.collector.plot_comparison_results(comparison)
        
        # 6. 生成分組報告
        self.generate_group_reports(groups, comparison)
        
        print(f"\n🎉 分析完成！")
        return comparison
    
    def generate_group_reports(self, groups, comparison):
        """生成分組報告"""
        print(f"\n📝 各組最佳配置分析:")
        
        for group_name, experiments in groups.items():
            if not experiments:
                continue
                
            print(f"\n--- {group_name} 組 ---")
            
            # 找到該組中PSNR最高的配置
            best_psnr = -1
            best_config = None
            
            for exp in experiments:
                if exp in comparison:
                    psnr = comparison[exp].get('image_psnr', 0)
                    ssim = comparison[exp].get('image_ssim', 0)
                    print(f"  {exp:10s}: PSNR={psnr:5.2f}dB, SSIM={ssim:5.3f}")
                    
                    if psnr > best_psnr:
                        best_psnr = psnr
                        best_config = exp
            
            if best_config:
                print(f"  🏆 最佳: {best_config} (PSNR={best_psnr:.2f}dB)")
    
    def run_custom_analysis(self, experiment_patterns):
        """運行自定義分析（根據模式匹配）"""
        print(f"🎯 運行自定義分析: {experiment_patterns}")
        
        # 掃描可用實驗
        available_experiments = self.scan_available_experiments()
        
        # 過濾匹配的實驗
        target_experiments = self.filter_experiments_by_pattern(available_experiments, experiment_patterns)
        
        if not target_experiments:
            print("❌ 沒有找到匹配的實驗！")
            return
        
        # 確保基準實驗存在
        if self.baseline_name not in available_experiments:
            print(f"❌ 基準實驗 {self.baseline_name} 不存在！")
            return
        
        # 收集實驗
        to_collect = [self.baseline_name] + target_experiments
        collected, failed = self.collect_all_experiments(to_collect)
        
        # 執行比較
        target_experiments = [exp for exp in target_experiments if exp in collected]
        comparison = self.collector.compare_experiments(self.baseline_name, target_experiments)
        
        # 生成圖表
        self.collector.plot_comparison_results(comparison)
        
        return comparison

def main():
    analyzer = AutoQuantizationAnalyzer()
    
    print("SANeRF-HQ 自動化量化分析工具")
    print("=" * 50)
    
    while True:
        print(f"\n選擇分析模式:")
        print(f"1. 全面分析 (所有可用實驗)")
        print(f"2. 自定義分析 (指定實驗模式)")
        print(f"3. 掃描可用實驗")
        print(f"4. 退出")
        
        choice = input(f"請選擇 [1-4]: ").strip()
        
        if choice == '1':
            analyzer.run_comprehensive_analysis()
            
        elif choice == '2':
            print(f"\n輸入實驗模式 (用空格分隔，例如: Q1. Q2. Q3.):")
            patterns = input("模式: ").strip().split()
            if patterns:
                analyzer.run_custom_analysis(patterns)
            else:
                print("❌ 沒有輸入模式！")
                
        elif choice == '3':
            analyzer.scan_available_experiments()
            
        elif choice == '4':
            print("👋 再見！")
            break
            
        else:
            print("❌ 無效選擇！")

if __name__ == "__main__":
    main()