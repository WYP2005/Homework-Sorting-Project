# 41243210
# 41243231

作業一

## 解題說明

本題要求測試4種排序方法，他們的效率時間範圍，並因此做出複合排序函數（Composite Sorting Function），使其能對所有 n 提供最佳性能

### 解題策略



## 程式實作

Insertion Sort

```cpp
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

void insertSort(int* a, int n){
    for(int i = 2; i <= n; i++){
        a[0] = a[i];

        int j = i - 1;
        for(; j >= 1 && a[0] < a[j]; j--){
            a[j + 1] = a[j];
        }

        a[j + 1] = a[0];
    }
}

bool checksort(int* a, int n){
    for(int i = 1; i < n; i++)
        if(a[i] > a[i+1]) return false;
    return true;
}

int main(){
    ifstream in;
    int n;
    in.open("data.txt");
    in >> n;
    int a[n+1];
    
    for(int i = 1; i < n; i++)
        in >> a[i];

    double start, stop;
    start = clock();
    insertSort(a, n);
    stop = clock();

    // for(int i = 1; i <= n; i++) cout << a[i] << " ";
    cout << checksort(a, n) << endl;
    cout << "執行時間:" << (stop - start) / CLOCKS_PER_SEC << "s" << endl;

    in.close();
}
```

Quick Sort

```cpp
    #include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
using namespace std;

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

template<class T>
bool checksort(vector<T>& a, int n){
    for(int i = 0; i < n - 1; i++)
        if(a[i] > a[i+1]) return false;
    return true;
}

int main(){
    ifstream in;
    int n;
    in.open("data.txt");
    in >> n;
    vector<int> a(n);
    
    double start, stop;
    for(int i = 0; i < n; i++)
        in >> a[i];

    start = clock();
    quicksort(a, 0, n - 1);
    stop = clock();

    // for(int i = 0; i < n; i++) cout << a[i] << " ";
    // cout << endl;
    cout << checksort(a, n) << endl;
    cout << "執行時間:" << (stop - start) / CLOCKS_PER_SEC << endl;
   
    in.close();
}

```

Merge Sort

```cpp
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

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

template<class T>
bool checksort(vector<T>& a, int n){
    for(int i = 0; i < n - 1; i++){
        if(a[i] > a[i+1]) return false;
    }
    return true;
}

int main(){
    ifstream in;
    int n;
    in.open("data.txt");
    in >> n;
    vector<int> test(n);
    for(int i = 0; i < n; i++){
        in >> test[i];
    }

    double start, stop;
    start = clock();
    mergesort(test, 0, n - 1);
    stop = clock();

    // for(int i = 0; i < n; i++) cout << test[i] << " ";
    // cout << endl;
    cout << checksort(test, n) << endl;
    cout << "執行時間:" << (stop - start) / CLOCKS_PER_SEC<< endl;

    in.close();
}
```

Heap Sort

```cpp
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

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

template<class T>
bool checksort(vector<T>& a, int n){
    for(int i = 0; i < n - 1; i++){
        if(a[i] > a[i+1]) return false;
    }
    return true;
}

int main(){
    ifstream in;
    int n;
    in.open("data.txt");
    in >> n;
    vector<int> test(n);
    for(int i = 0; i < n; i++){
        in >> test[i];
    }

    double start, stop;
    start = clock();
    heapsort(test);
    stop = clock();

    // for(int i = 0; i < n; i++) cout << test[i] << " ";
    cout << checksort(test, n) << endl;
    cout << "執行時間:" << (stop - start) / CLOCKS_PER_SEC << "s" << endl;

    in.close();
}
```

## 效能分析

1. 時間複雜度：程式的時間複雜度為 $O(\log n)$。
2. 空間複雜度：空間複雜度為 $O(100\times \log n + \pi)$。

## 測試與驗證

### 時間精確度:s

### 不同排序最糟情況運行時間
| 測試案例 | 輸入參數 $n$ | Insertion Sort(5次平均) | Merge Sort(5次平均) |Heap Sort(20組取最大) | Quick Sort(5次平均 |
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
| Insertion Sort   | 小數據 $n <= 32$      | 小數據處理快速、記憶體占用小        | 
| Merge Sort   | 大數據、需要穩定排序      | 各種情況時間複雜度都為O(nlogn)        | 
| Heap Sort   | 大數據、記憶體占用需少     | 記憶體占用小      | 
| Quick Sort   | 大數據      | 雖然最糟情況會到O(n^2)，但平均快       | 

### 綜合函數排序與其他排序運行時間表

| 測試案例 | 輸入參數 $n$ | Insertion Sort(5次平均) | Merge Sort(5次平均) |Heap Sort(20組取最大) | Quick Sort (5次平均)|Composite Sorting Function(50組平均) |
|----------|--------------|----------|----------|----------|----------|----------|
| 測試一   | $n = 500$      | 0.0004        | 0.0002        |0.001         |0.0001        |0        |
| 測試二   | $n = 1000$      | 0.001        | 0.001       |0.001        |0.0024       |0        |
| 測試三   | $n = 2000$      | 0.0048      |  0.0022       |0.003        |0.0096        |0        |
| 測試四   | $n = 3000$      | 0.01      | 0.0026        |0.004        |0.021       |0        |
| 測試五   | $n = 4000$     | 0.0166 | 0.003  |0.009      |  0.0344  |0        |
| 測試六   | $n = 5000$     | 0.0274 | 0.0038 |0.011       |    0.0566    |0        |

### 不同排序運行平均時間(50組平均)
| 測試案例 | 輸入參數 $n$ | Insertion Sort | Merge Sort |Heap Sort | Quick Sort |Composite Sorting Function |
|----------|--------------|----------|----------|----------|----------|----------|
| 測試一   | $n = 500$      | 0.00008       | 0.00128       |0.00016        |0.00006        |0.00006       |
| 測試二   | $n = 1000$      |  0.00032        | 0.00252       |0.00032       |0.00014         |0.00014        |
| 測試三   | $n = 2000$      | 0.00128       | 0.00542        |0.00072       |0.0003        |0.0003       |
| 測試四   | $n = 3000$      | 0.00294        | 0.00762        |0.00108      |0.00046       |0.00044        |
| 測試五   | $n = 4000$     | 0.0048 | 0.00984  |0.0015       |0.00064        |0.00062         |
| 測試六   | $n = 5000$     | 0.0075 | 0.01234 |0.00194        |0.0008        |0.00082        |


### 編譯與執行指令

```shell
$ g++ -std=c++17 -o sigma sigma.cpp
$ ./sigma
6
```

### 結論




