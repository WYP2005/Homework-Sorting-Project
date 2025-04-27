# 41243210
# 41243231

作業一

## 解題說明

本題要求測試4種排序方法，在最壞資料情況下獲取他們的效率時間範圍，並出複合排序函數（Composite Sorting Function），使其能對所有 n 提供最佳性能

### 解題策略
1.實作四種排序法：Insertion Sort、Quick Sort（使用 median-of-three）、Merge Sort（使用非遞迴法）、Heap Sort。

2.用4種排序法測試他們各自最壞情況下的時間複雜度（n = 30,500, 1000, ..., 5000,10000）。

3.測試平均情況下的時間複雜度（使用亂數產生資料）。

4.比較結果並畫圖。

5.寫出綜合排序函式（Composite Sort Function），並再做比較


## 程式實作
讀取文字檔案

```cpp
vector<int> read_data(const string& filename, int& n) {
    ifstream in;
    in.open(filename);
    if (!in.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    // 讀入資料筆數
    in >> n;
    vector<int> a(n);

    // 讀入資料
    for (int i = 0; i < n; i++) {
        if (!(in >> a[i])) {
            in.close();
            throw runtime_error("Invalid data format in file: " + filename);
        }
    }

    in.close();
    return a;
}
```
寫入文字檔案

```cpp
void write_to_file(const vector<int>& data, const string& filename) {
    ofstream out(filename);
    out << data.size() << endl;
    for (int i = 0; i < data.size(); i++) {
        out << data[i];
        if (i < data.size() - 1) out << " ";
    }
    out << endl;
    out.close();
}
```


生成insertion最糟糕的資料

```cpp
void generate_insertion_worst(int n) {
    vector<int> data(n);
    for (int i = 0; i < n; i++) {
        data[i] = n - i;
    }
    write_to_file(data, "data.txt");
}
}
```

merge和heap的前置生成函數


```cpp
void permute(vector<int>& arr, int n) {
    for (int i = n - 1; i >= 1; --i) {
        int j = rand() % (i + 1); // Random index from 0 to i
        swap(arr[i], arr[j]);
    }
}
```
生成merge最糟糕資料

```cpp
void generate_merge_worst(int n) {
    srand(time(0));
    vector<int> arr(n);

    // Initialize array with 1 to n
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }

    // Generate one random permutation
    permute(arr, n);
    write_to_file(arr, "data.txt");
}
```
生成heap最糟資料

```cpp
void generate_heap_worst(int n) {
    srand(time(0));
    vector<int> arr(n);

    // Initialize array with 1 to n
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }

    // Generate one random permutation
    permute(arr, n);
    write_to_file(arr, "data.txt");
}
```

生成隨機資料

```cpp
void generate_random_data(int n) {
    ofstream out("data.txt");
    if (!out.is_open()) {
        cerr << "無法開啟檔案: " << "data.txt" << endl;
        return;
    }

    srand(time(NULL)); // 設定隨機種子

    out << n << endl; // 寫入資料筆數
    for (int i = 0; i < n; i++) {
        out << rand() % n << " ";
    }
    out << endl;

    out.close();
}
```


Insertion Sort

```cpp
template<class T>
vector<T> insertsort(vector<T> a, int n){
    T temp;
    for(int i = 1; i < n; i++){
        temp = a[i];
        int j = i - 1;
        while(j >= 0 && temp < a[j]){
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = temp;
    }
    return a;
}
```

Quick Sort

```cpp
template<class T>
void quicksort(vector<T>& a, int left, int right){
    if(left < right){
        int mid = a[(left+right)/2], pivot;

        // 取三個數的中間值
        pivot = left;
        if((a[left] >= mid && mid >= a[right]) || (a[left] <= mid && mid <= a[right]))
            pivot = (left+right) / 2;
        if((a[right] >= a[left] && a[right] <= mid) || (a[right] <= a[left] && a[right] >= mid))
            pivot = right;

        // 將pivot移到最左邊
        swap(a[left], a[pivot]);
        int i = left, j = right + 1;
        do{
            do i++; while(a[i] < a[left]);
            do j--; while(a[j] > a[left]);
            if(i < j) swap(a[i], a[j]);
        }while(i < j);
        
        swap(a[left], a[j]);
        
        quicksort(a, left, j - 1);
        quicksort(a, j + 1, right);
    }

}
```

Merge Sort

```cpp
// 將左右陣列合併並排列
template<class T>
void merge(vector<T>& a, const int& front, const int& mid, const int& end){
    int i, j, count;
    i = j = 0;
    count = front;
    vector<T>   left(a.begin()+front, a.begin()+mid+1), 
                right(a.begin()+mid+1, a.begin()+end+1);

    // 若左陣列和右邊界都還沒到底，繼續比較
    while(i < left.size() && j < right.size()){
        if(left[i] < right[j]){
            a[count] = left[i];
            i++;
        }
        else{
            a[count] = right[j];
            j++;
        }
        count++;
    }

    // 將剩下的數值填入結果
    while(i < left.size())
        a[count++] = left[i++];
    while(j < right.size())
        a[count++] = right[j++];

}

template<class T>
void mergesort(vector<T>& a, const int& front, const int& end){

    if(front < end){
        int mid;
        mid = (front+end) / 2;
        mergesort(a, front, mid);
        mergesort(a, mid+1, end);
        merge(a, front, mid, end);
    }
}
```

Heap Sort

```cpp
template<class T>
void maxheapify(vector<T>& a, const int& root, const int& len){
    int left = 2*root+1;
    int right = 2*root+2;
    int largest = root;

    if(left < len && a[left] >= a[largest]){
        largest = left;
    }
    
    if(right < len && a[right] >= a[largest]){
        largest = right;
    }

    if(largest != root){
        swap(a[root], a[largest]);
        maxheapify(a, largest, len);
    }
}

// 建立最大堆積樹
template<class T>
void maxheap(vector<T>& a){
    for(int i = a.size()/2; i >= 0; i--){
        maxheapify(a, i, a.size());
    }
}

template<class T>
void heapsort(vector<T>& a){
    int len = a.size();
    maxheap(a);
    for(int i = a.size()-1; i > 0; i--){
        swap(a[i], a[0]);
        // 減掉以排序的長度在找下個最大堆積
        maxheapify(a, 0, --len);
    }
}
```

## 效能分析

### 不同排序的空間複雜度
| 排序演算法 | 空間複雜度| 
|----------|--------------|
| Insertion Sort   | O($1$) |
| Merge Sort   | O($n log n$)|
| Heap Sort   | O($n log n$) |
| Quick Sort   | O($n log n$)

### 不同排序的時間複雜度
| 排序演算法 | Best| Worst| Avg| 
|----------|--------------|--------------|--------------|
| Insertion Sort   | O($n$)  | O($n^2$) | O($n^2$) |
| Merge Sort   | O($n log n$)  | O($n log n$) | O($n log n$) |
| Heap Sort   | O($n log n$)   | O($n log n$) | O($n log n$) |
| Quick Sort   | O($n log n$)  | O($n^2$) | O($n log n$)

### 計時方式
使用在<ctime>中的clock()，單位為毫秒
用法如以下程式
```c++
start = clock();
insertsort(a, n);
stop = clock();
(stop - start) / CLOCKS_PER_SEC // 轉成秒
```

### 時間精確度:s
### 不同排序最糟情況運行時間
| 測試案例 | 輸入參數 $n$ | Insertion Sort(55次平均) | Quick Sort(55次平均) | Merge Sort(20組取最大)|Heap Sort(20組取最大) |
|----------|--------------|----------|----------|----------|----------|
| 測試一   | $n = 30$      | 0       | 0       |0.002        |0  |
| 測試二   | $n = 500$      | 0.000618182        | 0.0000909     |0.002        |0.001 |
| 測試三   | $n = 1000$      | 0.00238182       | 0.000218182       |0.002       |0.001       |
| 測試四   | $n = 2000$      | 0.00958182      | 0.0034     |0.003        |0.001    |
| 測試五   | $n = 3000$     | 0.0218182 |0.00754545 | 0.004  |   0.001    |
| 測試六   | $n = 4000$     |  0.0392182|0.0133818|  0.005    |0.002     |
| 測試七   | $n = 5000$     |  0.0600909|0.0208545 |  0.006    |0.003     |
| 測試八   | $n = 10000$     |  0.238436|0.0834545 |  0.012    |0.004     |

根據以上測出來的資料可以看出Insertion Sort符合最壞情況(O($n^2$) Quick Sort符合最壞情況(O($n^2$) Merge Sort符合最壞情況O($n log n$)  Heap Sort符合最壞情況O($n log n$)，這4個排序法都複合他們最壞情況的時間複雜度


### 不同排序運行效率最佳範圍
| 排序演算法 | 最佳效率範圍| 理由 |
|----------|--------------|----------|
| Insertion Sort   | 小數據 $n <= 30$      | 小數據處理快速、記憶體占用小        | 
| Merge Sort   | $n >= 2000$     | 各種情況時間複雜度都為O(nlogn)        | 
| Heap Sort   | $n <= 2000     | 記憶體占用小      | 
| Quick Sort   | $n >= 500$      | 雖然最糟情況會到O(n^2)，但平均快       | 


### 不同排序運行平均時間(20組平均)
| 測試案例 | 輸入參數 $n$ | Insertion Sort | Quick Sort |Merge Sort | Heap Sort |Composite Sorting Function |
|----------|--------------|----------|----------|----------|----------|----------|
| 測試一   | $n = 30$      | 0        | 0        |0      |0         |0.00005      |
| 測試二   | $n = 500$     | 0.0001  | 0.00005   |0.00015      |0.0001   |0.00005       |
| 測試三   | $n = 1000$    | 0.0007  | 0.00005  |0.00035      |0.0001    |0.000105263       |
| 測試四   | $n = 2000$    | 0.00265  | 0.0001   |0.001     |0.0001   |0.000421053        |
| 測試五   | $n = 3000$    | 0.0059  | 0.00015   |0.00125     |0.00065   |0.000578947         |
| 測試六   | $n = 4000$    | 0.0095  | 0.0005   |0.00155     |0.0007   |0.000789474        |
| 測試七   | $n = 5000$    | 0.01535   | 0.0006  |0.0023     |0.00095    |0.001        |
| 測試八   | $n = 10000$   | 0.0605  | 0.001  |0.0045     |0.00185    |0.00210526        |
| 測試九   | $n = 30000$   | 0.80815  | 0.0043   |0.0202     |0.00785   |0.00831579        |
| 測試十   | $n = 50000$   | 2.40035  | 0.0079   |0.0384      |0.0149   |0.0152105        |
根據以上測出來的資料可以看出Insertion Sort符合平均情況(O($n^2$) Quick Sort符合平均情況O($n log n$) Merge Sort符合平均情況O($n log n$)  Heap Sort符合平均情況O($n log n$)，這4個排序法都符合他們平均情況下的時間複雜度


## 測試與驗證





## 申論及開發報告

### 結論




