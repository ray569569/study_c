#!/usr/bin/env python3
"""
修正版 SANeRF-HQ 批量量化測試腳本
解決30秒超時問題
"""

import os
import sys
import subprocess
import json
import time
from pathlib import Path

class FixedBatchQuantizationTester:
    def __init__(self, base_config):
        self.base_config = base_config
        self.quantization_configs = self.generate_quantization_configs()
        self.results_dir = Path("./quantization_batch_results")
        self.results_dir.mkdir(exist_ok=True)
        
    def generate_quantization_configs(self):
        """生成量化配置列表"""
        configs = []
        
        #基準測試
        #configs.append({
        #    'name': 'FP32_baseline',
        #    'precision': 'FP32',
        #    'int_bits': None,
        #    'frac_bits': None
        #})
            
        ##Q4.x 系列
        for int_part in range(2, -1, -1):  
            configs.append({
                'name': f'Q{int_part}.0',
                'precision': f'Q{int_part}.0',
                'int_bits': int_part,
                'frac_bits': 0
            })
        #for frac_bits in range(5, -1, -1):  
        #    configs.append({
        #        'name': f'Q1.{frac_bits}',
        #        'precision': f'Q1.{frac_bits}',
        #        'int_bits': 1,
        #        'frac_bits': frac_bits
        #    })
        
        # FP16 測試
        #configs.append({
        #    'name': 'FP16_test',
        #    'precision': 'FP16',
        #    'int_bits': None,
        #    'frac_bits': None
        #})
        
        return configs
    
    def setup_quantization_environment(self, config):
        """設置量化環境變數"""
        env_vars = os.environ.copy()
        
        # 設置量化參數環境變數
        env_vars['SANERF_QUANTIZATION_TYPE'] = config['precision']
        if config['int_bits'] is not None:
            env_vars['SANERF_QUANTIZATION_INT_BITS'] = str(config['int_bits'])
        if config['frac_bits'] is not None:
            env_vars['SANERF_QUANTIZATION_FRAC_BITS'] = str(config['frac_bits'])
        
        return env_vars
    
    def run_single_test(self, config):
        """執行單一量化測試 - 修正版"""
        print(f"\n{'='*60}")
        print(f"Running test: {config['name']}")
        print(f"Precision: {config['precision']}")
        if config['int_bits'] is not None:
            print(f"Int bits: {config['int_bits']}, Frac bits: {config['frac_bits']}")
        print(f"{'='*60}")
        
        # 設置工作空間路徑
        workspace = f"./workspace/quantization_test/{config['name']}"
        # 構建命令 - 使用您的實際配置
        #cmd = [
        #    'python', 'main.py', self.base_config['data_path'],
        #    '--workspace', workspace,
        #    '--init_ckpt', self.base_config['init_ckpt'],
        #    '--mask_root', self.base_config['mask_path'],
        #    '--test_view_path', self.base_config.get('test_view_path', 'example_test_views.json'),
        #    '--enable_cam_center',
        #    '--with_mask',
        #    '--test',
        #    '--test_split', 'val',
        #    '--val_type', 'val_split',
        #    '--data_type', 'mip',
        #    '--contract',
        #    '--use_default_intrinsics',
        #    '--return_extra',
        #    '--render_mask_instance_id', '1'
        #]
        cmd = [
            'python', '-m', 'cProfile', '-o', 'profile.prof', 'main.py',
            self.base_config['data_path'],
            '--workspace', workspace,
            '--init_ckpt', self.base_config['init_ckpt'],
            '--enable_cam_center',
            '--data_type', 'mip',
            '--test',
            '--test_split', 'val',
            '--val_type', 'val_all',
            '--with_sam',
            '--num_rays', '8192',
            '--contract',
            '--sam_use_view_direction',
            '--feature_container', 'cache',
            '--decode',
            '--use_point',
            '--point_file', 'example_points.json'
        ]

        
        
        # 設置環境變數
        env = self.setup_quantization_environment(config)
        
        # 執行測試 - 增加超時時間到10分鐘
        start_time = time.time()
        print(f"🏃 執行命令: {' '.join(cmd)}")
        print(f"📁 工作空間: {workspace}")
        
        try:
            # 使用更長的超時時間，並顯示即時輸出
            process = subprocess.Popen(
                cmd, 
                env=env,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                text=True,
                bufsize=1,
                universal_newlines=True
            )
            
            # 即時顯示輸出
            output_lines = []
            while True:
                output = process.stdout.readline()
                if output == '' and process.poll() is not None:
                    break
                if output:
                    print(f"  {output.strip()}")
                    output_lines.append(output)
                    
                # 檢查是否執行太久 (15分鐘超時)
                if time.time() - start_time > 900:
                    print("⏰ 測試執行時間過長，終止測試")
                    process.terminate()
                    process.wait()
                    break
            
            return_code = process.poll()
            end_time = time.time()
            execution_time = end_time - start_time
            
            if return_code == 0:
                print(f"✅ Test {config['name']} completed successfully in {execution_time:.2f}s")
                
                # 記錄結果
                result_info = {
                    'config': config,
                    'execution_time': execution_time,
                    'status': 'success',
                    'workspace': workspace,
                    'timestamp': time.strftime('%Y-%m-%d %H:%M:%S'),
                    'output': ''.join(output_lines)
                }
                
                return result_info
            else:
                print(f"❌ Test {config['name']} failed with return code {return_code}")
                
                return {
                    'config': config,
                    'execution_time': execution_time,
                    'status': 'failed',
                    'return_code': return_code,
                    'output': ''.join(output_lines),
                    'timestamp': time.strftime('%Y-%m-%d %H:%M:%S')
                }
                
        except Exception as e:
            end_time = time.time()
            execution_time = end_time - start_time
            print(f"💥 Test {config['name']} crashed: {str(e)}")
            return {
                'config': config,
                'execution_time': execution_time,
                'status': 'crashed',
                'error': str(e),
                'timestamp': time.strftime('%Y-%m-%d %H:%M:%S')
            }
    
    def run_batch_tests(self, start_from=0, max_tests=None):
        """執行批量測試"""
        print(f"🚀 Starting batch quantization tests")
        print(f"Total configurations: {len(self.quantization_configs)}")
        print(f"Results will be saved to: {self.results_dir}")
        
        # 檢查是否有之前的進度
        progress_file = self.results_dir / "progress.json"
        completed_tests = set()
        
        if progress_file.exists():
            try:
                with open(progress_file, 'r') as f:
                    progress_data = json.load(f)
                    completed_tests = set(progress_data.get('completed', []))
                print(f"📋 發現之前的進度，已完成 {len(completed_tests)} 個測試")
            except:
                pass
        
        results = []
        configs_to_test = self.quantization_configs[start_from:]
        if max_tests:
            configs_to_test = configs_to_test[:max_tests]
        
        for i, config in enumerate(configs_to_test, start_from + 1):
            # 跳過已完成的測試
            if config['name'] in completed_tests:
                print(f"⏭️  跳過已完成的測試: {config['name']}")
                continue
                
            print(f"\n🔄 Progress: {i}/{len(self.quantization_configs)}")
            
            result = self.run_single_test(config)
            results.append(result)
            
            # 記錄完成的測試
            completed_tests.add(config['name'])
            
            # 即時保存結果和進度
            self.save_intermediate_results(results)
            self.save_progress(completed_tests)
            
            # 簡短休息以避免GPU過熱
            print("⏱️  冷卻中...")
            time.sleep(3)
        
        # 最終保存結果
        self.save_final_results(results)
        return results
    
    def save_progress(self, completed_tests):
        """保存進度"""
        progress_file = self.results_dir / "progress.json"
        progress_data = {
            'completed': list(completed_tests),
            'timestamp': time.strftime('%Y-%m-%d %H:%M:%S')
        }
        with open(progress_file, 'w') as f:
            json.dump(progress_data, f, indent=2)
    
    def save_intermediate_results(self, results):
        """保存中間結果"""
        result_file = self.results_dir / "intermediate_results.json"
        with open(result_file, 'w') as f:
            json.dump(results, f, indent=2)
    
    def save_final_results(self, results):
        """保存最終結果"""
        result_file = self.results_dir / "final_results.json"
        with open(result_file, 'w') as f:
            json.dump(results, f, indent=2)
        
        # 生成摘要報告
        self.generate_summary_report(results)
    
    def generate_summary_report(self, results):
        """生成摘要報告"""
        summary_file = self.results_dir / "summary_report.txt"
        
        successful_tests = [r for r in results if r.get('status') == 'success']
        failed_tests = [r for r in results if r.get('status') != 'success']
        
        with open(summary_file, 'w') as f:
            f.write("SANeRF-HQ 批量量化測試摘要報告\n")
            f.write("=" * 50 + "\n\n")
            
            f.write(f"總測試數: {len(results)}\n")
            f.write(f"成功測試: {len(successful_tests)}\n")
            f.write(f"失敗測試: {len(failed_tests)}\n\n")
            
            if successful_tests:
                f.write("成功的測試:\n")
                for result in successful_tests:
                    config = result['config']
                    f.write(f"  - {config['name']}: {result['execution_time']:.2f}s\n")
            
            if failed_tests:
                f.write("\n失敗的測試:\n")
                for result in failed_tests:
                    config = result['config']
                    f.write(f"  - {config['name']}: {result.get('status', 'unknown')}\n")
        
        print(f"\n📊 Summary report saved to: {summary_file}")

def main():
    # 配置基礎參數 (請根據您的環境調整)
    base_config = {
        'data_path': '/home/ray/SANeRF-HQ/dataset/bonsai',
        'mask_path': './workspace/sam_nerf/bonsai/object_masks',
        'init_ckpt': './workspace/rgb_nerf/bonsai/checkpoints/ngp_ep0019.pth',
        'test_view_path': 'example_test_views.json',
    }
    
    # 創建測試器
    tester = FixedBatchQuantizationTester(base_config)
    
    # 顯示將要測試的配置
    print("將要測試的量化配置:")
    for i, config in enumerate(tester.quantization_configs):
        print(f"  {i+1:2d}. {config['name']}")
    
    # 確認開始測試
    response = input(f"\n要開始批量測試嗎? (總共 {len(tester.quantization_configs)} 個配置) [y/N]: ")
    if response.lower() != 'y':
        print("測試已取消")
        return
    
    # 詢問是否從特定位置開始
    start_from = 0
    resume_response = input("是否要從特定配置開始? (輸入編號，或按Enter從頭開始): ")
    if resume_response.strip().isdigit():
        start_from = int(resume_response.strip()) - 1
        start_from = max(0, min(start_from, len(tester.quantization_configs) - 1))
        print(f"將從第 {start_from + 1} 個配置開始")
    
    # 執行批量測試
    results = tester.run_batch_tests(start_from=start_from)
    
    print(f"\n🎉 批量測試完成!")
    print(f"結果保存在: {tester.results_dir}")
    print(f"成功測試: {len([r for r in results if r.get('status') == 'success'])}")
    print(f"失敗測試: {len([r for r in results if r.get('status') != 'success'])}")

if __name__ == "__main__":
    main()