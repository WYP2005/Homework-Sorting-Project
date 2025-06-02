# 41243210
# 41243231

作業二

## 解題說明

寫一個具有插入和刪除指定節點的二元搜尋樹

### 解題策略


## 程式實作
所使用到的所有函式庫和namespace
```cpp
#include <iostream>
#include <random>
#include <cmath>
#include <utility>
#include <vector>
using namespace std;
```
BST的抽象母類別
宣告所有BST會用到的抽象函數
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
樹的節點類別
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


針對抽象類別Dictionary的BST類別完整宣告
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


遞迴版本的取得節點高度

```cpp
template <class K, class E>
int BST<K, E>::height(TreeNode<K, E>* node) const {
    if (!node) return 0;
    return 1 + max(height(node->leftChild), height(node->rightChild));
}
```
檢查樹是不是空的
```cpp
template <class K, class E>
bool BST<K, E>::IsEmpty() const {
    return root == 0;
}
```

查找某個key

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


BST插入key和value的實作功能函數
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

找尋中序後繼節點
```cpp
template <class K, class E>
TreeNode<K, E>* BST<K, E>::findMin(TreeNode<K, E>* node) {
    if (node == 0 || node->leftChild == 0) return node;
    return findMin(node->leftChild);
}
```
BST的刪除實作功能函數
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

類別外部取得BST高度的函數
```cpp
template <class K, class E>
int BST<K, E>::getHeight() const {
    return height(root);
}
```

陣列洗牌打亂順序讓結果更接近2
```cpp
void permute(vector<int>& arr, int n, mt19937& gen) {
    for (int i = n - 1; i >= 1; --i) {
        int j = gen() % (i + 1); // 隨機索引 [0, i]
        swap(arr[i], arr[j]);
    }
}
```
主程式的實作
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
### 各數值的比值表(10次取平均)
| 測試案例 | 輸入參數 $n$ | 高度 | 高度除以log2n比值| 
|----------|--------------|----------|----------|
| 測試一   | $n = 100$      | 13.8      |2.0772|
| 測試二   | $n = 500$      | 20.0	        | 2.2308     |
| 測試三   | $n = 1000$      | 20.9       | 2.0072       |
| 測試四   | $n = 2000$      |24.3	      | 2.1159     |
| 測試五   | $n = 3000$     | 26.2 |2.2683 | 
| 測試六   | $n = 10000$     |  31.6	|2.3781|  

根據上述表格可以看出總體比值大概都是為2開頭上下


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




根據以上測出來的資料可以看出Insertion Sort符合平均情況(O($n^2$) Quick Sort符合平均情況O($n log n$) Merge Sort符合平均情況O($n log n$)  Heap Sort符合平均情況O($n log n$)，這4個排序法都符合他們平均情況下的時間複雜度

![平均空間折線圖](https://github.com/user-attachments/assets/8e1bda6c-eb51-485f-8732-f9fc28dde12b)



## 申論及開發報告
測試所使用每個排序的最糟情況產生  
插入排序:產生由n、n-1~0由大到小的資料  
快速排序:沿用插入排序的最糟測資，並更改選擇pivot的邏輯，讓pivot每次都選到最大值  
整合排序和堆積排序:利用 permute() 函式實作 Fisher-Yates 洗牌法，確保每一個排列機率相同，隨機產生20組測試資料，並從中選出所需時間最久的  
  
在寫composite sort時，利用了quick sort當作預設的排序方式，因為速度最快。在遞迴深度過高或需排序長度較低時，採用了heap sort和insertion sort，速度相差不多的情況下又能減少記憶體空間占用。




