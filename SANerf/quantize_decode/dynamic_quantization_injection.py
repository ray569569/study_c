"""
動態量化注入模組
通過環境變數動態控制量化精度，無需重複修改代碼
"""

import os
import torch
from quantization_plugin import QuantizationPlugin

class DynamicQuantizationManager:
    """動態量化管理器 - 根據環境變數自動配置"""
    
    def __init__(self):
        self.quantizer = self._create_quantizer_from_env()
        print(f"🔧 Quantization Mode: {self.get_current_config()}")
    
    def _create_quantizer_from_env(self):
        """根據環境變數創建量化器"""
        
        # 從環境變數讀取配置
        quant_type = os.getenv('SANERF_QUANTIZATION_TYPE', 'FP32')
        int_bits = os.getenv('SANERF_QUANTIZATION_INT_BITS')
        frac_bits = os.getenv('SANERF_QUANTIZATION_FRAC_BITS')
        
        if quant_type == 'FP32':
            # 對照組：不量化
            return QuantizationPlugin(enabled=False)
        
        elif quant_type == 'FP16':
            # FP16模式
            return QuantizationPlugin("FP16", enabled=True)
        
        elif quant_type.startswith('Q') and int_bits and frac_bits:
            # 固定點量化模式
            return QuantizationPlugin(
                precision_type=quant_type,
                int_bits=int(int_bits),
                frac_bits=int(frac_bits),
                enabled=True
            )
        
        else:
            print(f"⚠️  Unknown quantization config, falling back to FP32")
            return QuantizationPlugin(enabled=False)
    
    def get_current_config(self):
        """獲取當前量化配置資訊"""
        quant_type = os.getenv('SANERF_QUANTIZATION_TYPE', 'FP32')
        if quant_type == 'FP32':
            return "FP32 (Baseline - No Quantization)"
        elif quant_type == 'FP16':
            return "FP16 (Half Precision)"
        else:
            int_bits = os.getenv('SANERF_QUANTIZATION_INT_BITS', 'N/A')
            frac_bits = os.getenv('SANERF_QUANTIZATION_FRAC_BITS', 'N/A')
            return f"{quant_type} (Int: {int_bits}, Frac: {frac_bits})"
    
    def quantize(self, tensor):
        """量化張量"""
        return self.quantizer(tensor)
    
    def __call__(self, tensor):
        """使對象可調用"""
        return self.quantize(tensor)

# 全域量化管理器實例
_global_quant_manager = None

def get_quantization_manager():
    """獲取全域量化管理器"""
    global _global_quant_manager
    if _global_quant_manager is None:
        _global_quant_manager = DynamicQuantizationManager()
    return _global_quant_manager

def quantize_tensor(tensor):
    """便捷的張量量化函數"""
    return get_quantization_manager()(tensor)
