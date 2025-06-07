
import math
import matplotlib.pyplot as plt

# 參數
ts = 0.08
tl = 0.02
tr = 0.001
n = 200000
m = 64
S = 2000
tcpu = 1000

# 計算 t_input
k_values = [2, 4, 8, 16, 32, 64]
t_input_values = []

for k in k_values:
    p = math.ceil(math.log(m, k))
    B = S // (2 * k + 2)
    io_per_pass = math.ceil(n / B)
    t_io = ts + tl + B * tr
    t_input = p * io_per_pass * t_io
    t_input_values.append(t_input)

# 輸出結果
for k, t in zip(k_values, t_input_values):
    print(f"k = {k:>2}, t_input = {t:.2f} s")

# 繪圖
plt.plot(k_values, t_input_values, marker='o')
plt.axhline(y=tcpu, color='r', linestyle='--', label='t_cpu = 1000 s')
plt.xlabel("k (merge ways)")
plt.ylabel("t_input (秒)")
plt.title("t_input 與 k 的關係")
plt.legend()
plt.grid(True)
plt.show()
