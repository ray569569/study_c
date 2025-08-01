import numpy as np

# 生成 weights (128 个随机数在 0.01 ~ 0.03 之间)
weights = np.random.uniform(0.01, 0.03, size=(1000, 128))  
weights_sum = np.sum(weights, axis=1)  # 计算总和
true_pdf = weights / weights_sum[:, None]  # 真实 pdf

# 计算 64 段区间的边界
num_segments = 64
weights_sum_min, weights_sum_max = 1.5, 3.8
weights_sum_bins = np.linspace(weights_sum_min, weights_sum_max, num_segments)

# 近似 1 / weights_sum (用移位逼近)
inv_approx = np.zeros(num_segments)

for i, ws in enumerate(weights_sum_bins):
    if ws >= 3.75:
        inv_approx[i] = 1 - (1/8 + 1/16 + 1/64)  # 乘以 0.265
    elif ws >= 3.71:
        inv_approx[i] = 1 - (1/8 + 1/16)  # 乘以 0.270
    elif ws >= 3.67:
        inv_approx[i] = 1 - (1/8 + 1/32)  # 乘以 0.275
    elif ws >= 3.63:
        inv_approx[i] = 1 - (1/8 + 1/64)  # 乘以 0.280
    elif ws >= 3.59:
        inv_approx[i] = 1 - (1/8)  # 乘以 0.285
    elif ws >= 3.55:
        inv_approx[i] = 1 - (1/8 - 1/32)  # 乘以 0.290
    else:
        inv_approx[i] = 1 / ws  # 极端情况使用真实倒数

# 运行时匹配区间
approx_pdf = np.zeros_like(true_pdf)
for i, ws in enumerate(weights_sum):
    idx = np.digitize(ws, weights_sum_bins) - 1  # 找到对应的 64 段区间
    approx_pdf[i] = weights[i, :] * inv_approx[idx]

# 计算百分比误差
percent_error = np.abs(true_pdf - approx_pdf) / true_pdf * 100

# 误差统计
max_percent_error = np.max(percent_error)
mean_percent_error = np.mean(percent_error)

print(f"最大百分比误差: {max_percent_error:.4f}%")
print(f"平均百分比误差: {mean_percent_error:.4f}%")
