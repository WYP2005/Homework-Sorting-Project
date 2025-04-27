# 41243210
# 41243231

作業一

## 解題說明

本題要求測試4種排序方法，他們的效率時間範圍，並因此做出複合排序函數（Composite Sorting Function），使其能對所有 n 提供最佳性能

### 解題策略



## 程式實作

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

## 測試與驗證

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

### 不同排序平均運行時間
| 測試案例 | 輸入參數 $n$ | Insertion Sort(20次平均) | Merge Sort(20次平均) |Heap Sort(20次平均) | Quick Sort(20次平均) |
|----------|--------------|----------|----------|----------|----------|
| 測試一   | $n = 500$      | 0.0004        | 0.0002       |0.001        |0.0001  |
| 測試二   | $n = 1000$      | 0.001        | 0.001      |0.001        |0.0024 |
| 測試三   | $n = 2000$      | 0.0048        | 0.0022        |0.003       |0.0096       |
| 測試四   | $n = 3000$      | 0.01       | 0.0026     |0.004        |0.021    |
| 測試五   | $n = 4000$     | 0.0166 |0.003  | 0.009  |   0.0344    |
| 測試六   | $n = 5000$     |  0.0274|0.0038 |  0.011    |0.0566     |

### 不同排序運行效率最佳範圍
| 排序演算法 | 最佳效率範圍| 理由 |
|----------|--------------|----------|
| Insertion Sort   | 小數據 $n <= 30$      | 小數據處理快速、記憶體占用小        | 
| Merge Sort   | $n >= 2000$     | 各種情況時間複雜度都為O(nlogn)        | 
| Heap Sort   | $n <= 2000     | 記憶體占用小      | 
| Quick Sort   | $n >= 500$      | 雖然最糟情況會到O(n^2)，但平均快       | 

### 不同排序運行平均時間(50組平均)
| 測試案例 | 輸入參數 $n$ | Insertion Sort | Quick Sort |Merge Sort | Heap Sort |Composite Sorting Function |
|----------|--------------|----------|----------|----------|----------|----------|
| 測試一   | $n = 30$      | 0        | 0        |0.0001      |0         |0.00006       |
| 測試二   | $n = 500$     | 0.00055  | 0.0001   |0.0016      |0.00025   |0.00014        |
| 測試三   | $n = 1000$    | 0.00215  | 0.00015  |0.0034      |0.0002    |0.0003       |
| 測試四   | $n = 2000$    | 0.00845  | 0.0002   |0.00675     |0.00075   |0.00044        |
| 測試五   | $n = 3000$    | 0.01945  | 0.0004   |0.01035     |0.00115   |0.00062         |
| 測試六   | $n = 4000$    | 0.03395  | 0.0007   |0.01405     |0.00165   |0.00082        |
| 測試七   | $n = 5000$    | 0.0525   | 0.00095  |0.01665     |0.0019    |0.00082        |
| 測試八   | $n = 10000$   | 0.20885  | 0.00175  |0.03545     |0.0044    |0.00082        |
| 測試九   | $n = 30000$   | 2.67215  | 0.0059   |0.10195     |0.01525   |0.00082        |
| 測試十   | $n = 50000$   | 7.56815  | 0.0103   |0.1698      |0.02575   |0.00082        |



## 申論及開發報告

### 結論




