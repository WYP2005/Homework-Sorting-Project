# 41243210

# 41243231

作業三
## 解題說明
**(a)：**  
推導外部排序第二階段（合併階段）的總輸入時間 $t_{\text{input}}$，這涉及緩衝區配置、合併次數、磁碟存取與傳輸時間。

**b)：**  
根據給定參數，計算不同 $k$ 值下的 $t_{\text{input}}$，繪製其與 $k$ 的關係圖，並判斷是否存在某個 $k$ 使得 $t_{\text{cpu}} \approx t_{\text{input}}$。
## 解題策略
### 練習 1(a)

1. **記憶體配置**  
   - 可用記憶體大小為 $S$ records  
   - 分為 $2k + 2$ 個 buffer（$2k$ 輸入緩衝區 + 2 輸出緩衝區）  
   - 每個 buffer 大小為 $B = \left\lfloor \frac{S}{2k + 2} \right\rfloor$

2. **合併次數**  
   - 初始有 $m$ 個 runs，所需合併次數為：  
     $$
     p = \lceil \log_k m \rceil
     $$

3. **I/O 操作次數**  
   - 每 pass 處理所有 $n$ 筆資料，每次 buffer 滿會做一次 I/O，總共約 $\lceil n / B \rceil$ 次

4. **每次 I/O 時間**  
   - 每次花費 $t_s + t_l + B \cdot t_r$

5. **總輸入時間公式**  
   $$
   ( t_{\text{input}} = p \cdot \lceil n / B \rceil \cdot (t_s + t_l + B \cdot t_r) )
   $$

---

### 練習 1(b)

**參數設定：**

| 參數     | 值                |
|----------|-------------------|
| $t_s$    | 0.08 秒           |
| $t_l$    | 0.02 秒           |
| $t_r$    | 0.001 秒 / record |
| $n$      | 200,000 records   |
| $m$      | 64 runs           |
| $S$      | 2000 records      |
| $t_{\text{cpu}}$ | 1000 秒     |


## 程式實作

```python
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
```
