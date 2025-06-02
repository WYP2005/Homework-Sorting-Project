# 41243210
# 41243231

作業二

## 解題說明

寫一個具有插入和刪除指定節點的二元搜尋樹

### 解題策略
1.實作四種排序：Insertion Sort、Quick Sort、Merge Sort、Heap Sort。

2.測試4種排序他們各自最壞情況下的時間複雜度（n = 30,500, 1000, ..., 5000,10000）。

3.測試平均情況下的時間複雜度（使用亂數產生資料）。

4.比較結果並畫圖。

5.寫出綜合排序函式（Composite Sort Function），再去比較另外4個排序


## 程式實作
所使用到的所有函式庫
```cpp
#include <iostream>
#include <random>
#include <cmath>
#include <utility>
#include <vector>
using namespace std;
```

讀取文字檔案

```cpp
template <class K, class E>
class Dictionary {
public:
    virtual bool IsEmpty() const = 0;
    virtual pair<K, E>* Get(const K&) const = 0;
    virtual void Insert(const pair<K, E>&) = 0;
    virtual void Delete(const K&) = 0;
    virtual TreeNode<K, E>* findMin(TreeNode<K, E>*) = 0;
};
```
寫入文字檔案

```cpp
template <class K, class E>
class TreeNode {
public:
    TreeNode* leftChild;
    TreeNode* rightChild;
    pair<K, E> data;
    TreeNode(pair<K, E> e) {
        this->data.first = e.first;
        this->data.second = e.second;
        this->leftChild = NULL;
        this->rightChild = NULL;
    }
};
```


生成insertion sort最糟糕的資料

```cpp
template <class K, class E>
class BST : public Dictionary<K, E> {
private:
    TreeNode<K, E>* root;
    int height(TreeNode<K, E>* node) const;

public:
    int count = 0;
    double total = 0;
    BST() { root = 0; }
    bool IsEmpty() const override;
    pair<K, E>* Get(const K&) const override;
    void Insert(const pair<K, E>&) override;
    void Delete(const K&) override;
    TreeNode<K, E>* findMin(TreeNode<K, E>*) override;
    int getHeight() const;
};
```

merge sort和heap sort的前置生成函數


```cpp
template <class K, class E>
int BST<K, E>::height(TreeNode<K, E>* node) const {
    if (!node) return 0;
    return 1 + max(height(node->leftChild), height(node->rightChild));
}
```
生成merge sort和heap sort最糟糕資料

```cpp
template <class K, class E>
bool BST<K, E>::IsEmpty() const {
    return root == 0;
}
```

生成隨機資料

```cpp
template <class K, class E>
pair<K, E>* BST<K, E>::Get(const K& k) const {
    TreeNode<K, E>* currentNode = root;
    while (currentNode) {
        if (k < currentNode->data.first)
            currentNode = currentNode->leftChild;
        else if (k > currentNode->data.first)
            currentNode = currentNode->rightChild;
        else
            return &(currentNode->data);
    }
    return 0;
}
```


Insertion Sort

```cpp
template <class K, class E>
void BST<K, E>::Insert(const pair<K, E>& thePair) {
    TreeNode<K, E>* p = root, * pp = 0;
    while (p) {
        pp = p;
        if (thePair.first < p->data.first)
            p = p->leftChild;
        else if (thePair.first > p->data.first)
            p = p->rightChild;
        else {
            p->data.second = thePair.second;
            return;
        }
    }
    p = new TreeNode<K, E>(thePair);
    if (root) {
        if (thePair.first < pp->data.first)
            pp->leftChild = p;
        else
            pp->rightChild = p;
    }
    else
        root = p;
}
```

Quick Sort

```cpp
template <class K, class E>
TreeNode<K, E>* BST<K, E>::findMin(TreeNode<K, E>* node) {
    if (node == 0 || node->leftChild == 0) return node;
    return findMin(node->leftChild);
}
```

```cpp
template <class K, class E>
void BST<K, E>::Delete(const K& k) {
    TreeNode<K, E>* p = root, * pp = 0;
    while (p && p->data.first != k) {
        pp = p;
        if (k < p->data.first)
            p = p->leftChild;
        else
            p = p->rightChild;
    }
    if (!p) return;

    if (p->leftChild && p->rightChild) {
        TreeNode<K, E>* successor = findMin(p->rightChild);
        p->data = successor->data;
        Delete(successor->data.first);
    }
    else {
        TreeNode<K, E>* nodeToDelete = p;
        if (pp) {
            if (p->leftChild)
                p = p->leftChild;
            else
                p = p->rightChild;
            if (nodeToDelete == pp->leftChild)
                pp->leftChild = p;
            else
                pp->rightChild = p;
        }
        else {
            root = p->leftChild ? p->leftChild : p->rightChild;
        }
        delete nodeToDelete;
    }
}
```

Merge Sort

```cpp
template <class K, class E>
int BST<K, E>::getHeight() const {
    return height(root);
}
```

Heap Sort

```cpp
void permute(vector<int>& arr, int n, mt19937& gen) {
    for (int i = n - 1; i >= 1; --i) {
        int j = gen() % (i + 1); // 隨機索引 [0, i]
        swap(arr[i], arr[j]);
    }
}
```

Composite sort
```c++
int main() {
    random_device rd;
    mt19937 gen(rd());

    BST<int, int> bst;

    cout << "n,Ratio\n"; 
        int n = 100;
        vector<int> keys(n);
        for (int j = 0; j < n; j++) {
            keys[j] = j + 1;
        }
        permute(keys, n, gen);
        for (int j = 0; j < n; j++) {
            int value = gen() % 1000000 + 1; 
            pair<int, int> p(keys[j], value);
            bst.Insert(p);
        }
        int h = bst.getHeight();
        double ratio = (double)h / log2(n);
        cout << n << "," << ratio << endl;
    return 0;
}
```

## 效能分析

### 不同排序的空間複雜度
| 排序演算法 | 空間複雜度| 
|----------|--------------|
| Insertion Sort   | O($1$) |
| Merge Sort   | O($n$)|
| Heap Sort   | O($1$) |
| Quick Sort   | O($log n$)



### 不同排序的時間複雜度
| 排序演算法 | Best| Worst| Avg| 
|----------|--------------|--------------|--------------|
| Insertion Sort   | O($n$)  | O($n^2$) | O($n^2$) |
| Merge Sort   | O($n log n$)  | O($n log n$) | O($n log n$) |
| Heap Sort   | O($n log n$)   | O($n log n$) | O($n log n$) |
| Quick Sort   | O($n log n$)  | O($n^2$) | O($n log n$)




### 不同排序運行效率最佳範圍
| 排序演算法 | 最佳效率範圍| 理由 |
|----------|--------------|----------|
| Insertion Sort   | $n <= 30$      | 小數據處理快速、記憶體占用小        | 
| Merge Sort   | $n >= 500$     | 各種情況時間複雜度都為O(nlogn)        | 
| Heap Sort   | $n >= 500$       | 記憶體占用小      | 
| Quick Sort   | $n >= 500$      | 平均最快       | 


## 測試與驗證

測試方式:
更新最大記憶體函式
```c++
void update_max_memory(size_t memory) {
    if (memory > max_memory_usage) {
        max_memory_usage = memory;
    }
}
```
對每個排序使用不同的測量方式
Insertion sort 只有新增一個暫存變數
```c++
update_max_memory(sizeof(temp));
```
Quick sort 看遞迴深度，每次有i,j,mid,piovt存
```c++
update_max_memory(depth * 4 * sizeof(int));
```
Merge sort 額外空間儲存左右陣列
```c++
size_t current_memory = memory_of_vector(left) + memory_of_vector(right);
update_max_memory(current_memory);
```
Heap sort 只有left、right、largest
```c++
update_max_memory(3 * sizeof(int)); 
```
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



![糟糕狀況折線圖](https://cdn.discordapp.com/attachments/930060410823016509/1366049723403735100/QtXVX4G8N9wAAAABJRU5ErkJggg.png?ex=680f8872&is=680e36f2&hm=c537541d964d58b2a77f98ea6fe97b23d203445aa6a92c8de89b9746891e0cf8&)
根據以上測出來的資料可以看出Insertion Sort符合最壞情況(O($n^2$) Quick Sort符合最壞情況(O($n^2$) Merge Sort符合最壞情況O($n log n$)  Heap Sort符合最壞情況O($n log n$)，這4個排序法都符合他們最壞情況的時間複雜度



### 不同排序運行平均時間(500組平均)
| 測試案例 | 輸入參數 $n$ | Insertion Sort | Quick Sort |Merge Sort | Heap Sort |Composite Sorting Function |
|----------|--------------|----------|----------|----------|----------|----------|
| 測試一   | $n = 30$      | 0.000004       | 0.000004       |0.000018     |0.000002        |0.000002      |
| 測試二   | $n = 500$     | 0.000234  | 0.000042   |0.0002      |0.000074  |0.000056       |
| 測試三   | $n = 1000$    | 0.00096  | 0.000102  |0.000492      |0.000156    |0.00011       |
| 測試四   | $n = 2000$    | 0.003678  | 0.000198   |0.001116     |0.000348   |0.000222        |
| 測試五   | $n = 3000$    | 0.011764  | 0.000418   |0.002088     |0.000712   |0.000426         |
| 測試六   | $n = 4000$    | 0.019884  | 0.000478   |0.00261     |0.00092   |0.000666        |
| 測試七   | $n = 5000$    | 0.027722   | 0.000644  |0.003374     |0.001156    |0.00084        |
| 測試八   | $n = 10000$   | 0.13326  | 0.001482  |0.007308     |0.002576    |0.002226        |
| 測試九   | $n = 30000$   | 1.272  | 0.004786   |0.021888     |0.008928   |0.0122722        |
| 測試十   | $n = 50000$   | 3.55914  | 0.00838   |0.038854      |0.016022   |0.026612        |



![平均狀況折線圖](https://cdn.discordapp.com/attachments/930060410823016509/1366437304755028028/B9Nmgo5UxVu2AAAAAElFTkSuQmCC.png?ex=68119a28&is=681048a8&hm=43816d88c0c0ee07828e5f22d17a7d135af9558e00173adbbcfe5cf42fbf05fa&)

根據以上測出來的資料可以看出Insertion Sort符合平均情況(O($n^2$) Quick Sort符合平均情況O($n log n$) Merge Sort符合平均情況O($n log n$)  Heap Sort符合平均情況O($n log n$)，這4個排序法都符合他們平均情況下的時間複雜度

![平均空間折線圖](https://github.com/user-attachments/assets/8e1bda6c-eb51-485f-8732-f9fc28dde12b)



## 申論及開發報告
測試所使用每個排序的最糟情況產生  
插入排序:產生由n、n-1~0由大到小的資料  
快速排序:沿用插入排序的最糟測資，並更改選擇pivot的邏輯，讓pivot每次都選到最大值  
整合排序和堆積排序:利用 permute() 函式實作 Fisher-Yates 洗牌法，確保每一個排列機率相同，隨機產生20組測試資料，並從中選出所需時間最久的  
  
在寫composite sort時，利用了quick sort當作預設的排序方式，因為速度最快。在遞迴深度過高或需排序長度較低時，採用了heap sort和insertion sort，速度相差不多的情況下又能減少記憶體空間占用。




