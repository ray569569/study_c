import struct

def q1_4_to_float(val):
    if val >= 128:
        val -= 256
    return val / 16.0

def float_to_fp32_hex(f):
    return f'{struct.unpack("<I", struct.pack("<f", f))[0]:08x}'

def float_to_q4_1(f):
    return int(f * 2)

with open("q1_4_reciprocal_case.v", "w") as f:
    f.write("case(t1)\n")
    for i in range(32):
        x_float = q1_4_to_float(i)
        if x_float == 0:
            y = float('inf')  # 防止除以零
            continue
        else:
            y = 1.0 / x_float
        y_q4_1 = float_to_q4_1(y)
        f.write(f"\t5'b{i:05b}: out5 = 16'h{y_q4_1};\n")
        # y_hex = float_to_fp32_hex(y)
        # f.write(f"\t5'b{i:05b}: out5 = 32'h{y_hex};\n")
    f.write("default: out5 = 32'hffffffff;\nendcase\n")
