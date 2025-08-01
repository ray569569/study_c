import torch
import struct

def spacing_fn(x): 
    return torch.where(x < 1, x / 2, 1 - 1 / (2 * x))

def q2_5_to_float(val):
    if val >= 128:
        val -= 256
    return val / 32.0

def quantize_to_q2_5(x_float):
    """將 float 強制量化為 Q2.5 精度 (只保留 7 bit 精度)"""
    return round(x_float * 32) / 32.0

def float_to_fp32_hex(f):
    return f'{struct.unpack("<I", struct.pack("<f", f))[0]:08x}'

# 開始產生 Verilog case 語句
print("case(t2)")
for i in range(256):
    x_float = q2_5_to_float(i)           # Q2.5 解碼成 float
    x_q = quantize_to_q2_5(x_float)      # 強制保留 Q2.5 精度
    x_tensor = torch.tensor(x_q, dtype=torch.float32)
    y = spacing_fn(x_tensor).item()
    y_hex = float_to_fp32_hex(y)
    print(f"\t8'b{i:08b}: out3 = 32'h{y_hex};")
print("default: out3 = 32'hffffffff;")
print("endcase")
