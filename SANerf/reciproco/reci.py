import numpy as np
import matplotlib.pyplot as plt

# 定義分段範圍
segments = [0.0001, 0.01, 0.05,0.075, 0.1,0.125, 0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.6,0.7,0.8,0.9, 1, 1.25,1.5, 2,2.5, 3, 4, 8, 16, 32, 64, 128, 256]  # 分段點

# 初始化存儲結果的變數
all_x = np.array([])
all_y = np.array([])
all_y_fit = np.array([])

# 遍歷每個分段
for i in range(len(segments) - 1):
    start = segments[i]
    end = segments[i + 1]
    
    # 1. 定義當前分段的數據範圍和目標函數
    x = np.linspace(start, end, 10000)  # 當前分段的 x 範圍
    y = 1 / x                          # 當前分段的目標函數 y = 1/x
    
    # 2. 使用 numpy.polyfit 進行二次逼近
    n = 3                              # 二次模型 (多項式階數為 2)
    coeff = np.polyfit(x, y, n)        # 使用 polyfit 進行二次回歸
    print(f'分段 [{start}, {end}] 的二次模型為：y = {coeff[0]:.6f}x^2 + {coeff[1]:.6f}x + {coeff[2]:.6f}')
    
    # 3. 計算二次模型的近似值
    y_fit = np.polyval(coeff, x)       # 使用二次模型計算近似值
    
    # 4. 計算當前分段的誤差
    error = np.abs(y - y_fit)          # 當前分段的誤差
    max_error_index = np.argmax(error) # 找到當前分段誤差最大的索引
    max_error_x = x[max_error_index]   # 誤差最大的點的 x 值
    max_error_y_actual = y[max_error_index]  # 誤差最大的點的真實值
    max_error_y_approx = y_fit[max_error_index]  # 誤差最大的點的近似值
    
    print(f'分段 [{start}, {end}] 的最大誤差：')
    print(f'- 誤差最大的點為 x = {max_error_x:.6f}')
    print(f'- 真實值為：{max_error_y_actual:.6f}')
    print(f'- 二次模型近似為：{max_error_y_approx:.6f}')
    print(f'- 誤差為：{error[max_error_index]:.6f}')
    print('---')
    
    # 5. 合併結果
    all_x = np.concatenate((all_x, x))
    all_y = np.concatenate((all_y, y))
    all_y_fit = np.concatenate((all_y_fit, y_fit))

# 6. 可視化原始函數與分段二次逼近結果
plt.figure()
plt.plot(all_x, all_y, 'b-', linewidth=1.5, label='y = 1/x')        # 原始函數 y = 1/x
plt.plot(all_x, all_y_fit, 'r--', linewidth=1.5, label='Piecewise Quadratic Approximation')  # 分段二次逼近結果
plt.legend()
plt.xlabel('x')
plt.ylabel('y')
plt.title('Piecewise Quadratic Approximation of y = 1/x')
plt.grid(True)
plt.show()