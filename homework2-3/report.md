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
   - 分為 $2k + 2$ 個 buffer（ $2k$ 輸入緩衝區 + 2 輸出緩衝區）  
   - 每個 buffer 大小為 $B = \left\lfloor \frac{S}{2k + 2} \right\rfloor$

2. **合併次數**  
   - 初始有 $m$ 個 runs，所需合併次數為：  
     p = ceil(logₖ m)


3. **I/O 操作次數**  
   - 每 pass 處理所有 $n$ 筆資料，每次 buffer 滿會做一次 I/O，總共約 $\lceil n / B \rceil$ 次

4. **每次 I/O 時間**  
   - 每次花費 $t_s + t_l + B \cdot t_r$

5. **總輸入時間公式**  
`t_input = p * ceil(n / B) * (t_s + t_l + B * t_r)`


---

### 練習 1(b)

**假設參數：**

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

# 計算
k_values = [2, 4, 8, 16, 32, 64]
analysis = []

for k in k_values:
    p = math.ceil(math.log(m, k))                  
    B = S // (2 * k + 2)                         
    io_per_pass = math.ceil(n / B)                 
    t_io = ts + tl + B * tr                        
    t_input = p * io_per_pass * t_io              
    analysis.append((k, p, B, io_per_pass, t_io, t_input))

# 表格輸出
print(f"{'k':>2} {'p':>3} {'B':>5} {'I/O 次數':>9} {'t_io (秒)':>10} {'t_input (秒)':>15}")
for k, p, B, io_count, t_io, t_input in analysis:
    print(f"{k:>2} {p:>3} {B:>5} {io_count:>9} {t_io:10.3f} {t_input:15.2f}")

# 繪圖
k_plot = [x[0] for x in analysis]
t_input_plot = [x[-1] for x in analysis]

plt.plot(k_plot, t_input_plot, marker='o')
plt.axhline(y=tcpu, color='r', linestyle='--', label='t_cpu = 1000 s')
plt.xlabel("k (merge ways)")
plt.ylabel("t_input (秒)")
plt.title("t_input and k realtionship")
plt.legend()
plt.grid(True)
plt.show()
```

## 效能分析

| $k$ 值 | 合併層數 $p$ | buffer 大小 $B$ | 每層 I/O 次數 | 單次 I/O 時間 | $t_{\text{input}}$ |
|--------|---------------|------------------|----------------|----------------|--------------------|
| 2      | 6             | 333              | 601            | 0.433 秒       | 1561.40 秒         |
| 4      | 3             | 200              | 1000           | 0.300 秒       | 900.00 秒          |
| 8      | 2             | 111              | 1802           | 0.211 秒       | 760.44 秒          |
| 16     | 2             | 58               | 3449           | 0.158 秒       | 1089.88 秒         |
| 32     | 2             | 30               | 6667           | 0.130 秒       | 1733.42 秒         |
| 64     | 1             | 15               | 13334          | 0.115 秒       | 1533.41 秒         |



以上數值由程式自動計算而來，略有四捨五入誤差


![關係圖](https://images-wixmp-ed30a86b8c4ca887773594c2.wixmp.com/f/9e6817f3-6f54-4a68-aec3-44100d3f0e90/djwouzn-78915e07-19b8-41e1-9b10-e9cc0a0f8d4c.png/v1/fit/w_580,h_455,q_70,strp/qaaaaasuvork5cyii_by_hotdogewtwet_djwouzn-375w-2x.jpg?token=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJzdWIiOiJ1cm46YXBwOjdlMGQxODg5ODIyNjQzNzNhNWYwZDQxNWVhMGQyNmUwIiwiaXNzIjoidXJuOmFwcDo3ZTBkMTg4OTgyMjY0MzczYTVmMGQ0MTVlYTBkMjZlMCIsIm9iaiI6W1t7ImhlaWdodCI6Ijw9NDU1IiwicGF0aCI6IlwvZlwvOWU2ODE3ZjMtNmY1NC00YTY4LWFlYzMtNDQxMDBkM2YwZTkwXC9kandvdXpuLTc4OTE1ZTA3LTE5YjgtNDFlMS05YjEwLWU5Y2MwYTBmOGQ0Yy5wbmciLCJ3aWR0aCI6Ijw9NTgwIn1dXSwiYXVkIjpbInVybjpzZXJ2aWNlOmltYWdlLm9wZXJhdGlvbnMiXX0.okSQUDiZBiUUZ5LuvFeN2bFtBFeCsTFpUvaSb4NUPKI)


## 測試與驗證

### 趨勢分析
- 當 $k$ 增大時，合併層數 $p$ 減少，但每層所需的 I/O 次數增加，因為每個 buffer 大小變小，導致需要更多次存取磁碟。

- 當 $k = 8$ 時， $t_{\text{input}}$ 最低，代表此時合併次數與 I/O 數達到平衡。

- 當 $k = 16$ 時， $t_{\text{input}} \approx 1198.77$ ，最接近  $t_{\text{cpu}} = 1000$ ，符合題意所要求平衡的 k 值附近。

### 驗證 CPU 與 I/O 平衡點
- 我們希望找到一個 $k$，使得 $t_{\text{cpu}} \approx t_{\text{input}}$，而觀察結果顯示 $k=8$ 與 k=16 是最佳候選。

- 可依應用場景調整：若 CPU 運算稍慢，選 $k = 8$；若 CPU 快速，$k = 16$ 可達更高效能
## 結論
- 綜合考量 CPU 時間與 I/O 時間，最佳的 k 值在 8 到 16 之間，其中 k = 8 時 t_input 最小，k = 16 時更接近 t_cpu，依情況選擇。


## 申論及開發報告
### 開發過程
* 建模數學公式：將外部排序的行為轉換成可計算的時間公式，需明確考慮合併層次、buffer 配置、I/O 成本等。

* 程式計算：使用 Python 撰寫計算程式，觀察 $k$ 值與輸入時間的變化。

* 視覺化分析：透過圖形視覺化，清楚呈現趨勢與最小值，快速定位最適 $k$。

### 學習心得
實作過程讓我深入理解外部排序中 I/O 操作與記憶體配置的 trade-off。





