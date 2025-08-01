import struct

def spacing_fn_inv(x):
    return 2 * x if x < 0.5 else 1 / (2 - 2 * x)

def q0_11_to_float(val):
    return val / 1024.0

def float_to_fp32_hex(f):
    return f'{struct.unpack("<I", struct.pack("<f", f))[0]:08x}'

with open("spacing_fn_inv_q0_11_case.v", "w") as f:
    f.write("case(t3)\n")
    for i in range(1024):
        x_float = q0_11_to_float(i)
        y = spacing_fn_inv(x_float)
        y_hex = float_to_fp32_hex(y)
        f.write(f"\t11'b{i:011b}: out4 = 32'h{y_hex};\n")
    f.write("default: out4 = 32'hffffffff;\nendcase\n")
