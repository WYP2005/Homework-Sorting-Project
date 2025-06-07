# 41243210
# 41243231

作業2-2

## 解題說明

本題需要實現一個具有插入和刪除指定節點功能的二元搜尋樹

### 解題策略
#### 1. 寫一個虛擬類別Dictionary
#### 2. 定義一個TreeNode節點類別
#### 3. 用BST繼承它並完善一些簡單的基本功能
#### 4. 定義插入功能的函數
##### 插入 (Insert)：

##### 從根節點開始，比較新鍵與當前節點鍵：

* 若新鍵小於當前節點鍵，移動到左子樹。
* 若新鍵大於當前節點鍵，移動到右子樹。
* 若鍵已存在，更新對應值。

若找到空位置（NULL），插入新節點。

#### 5. 定義刪除節點功能的函數
   
##### 刪除 (Delete)：

##### 首先找到要刪除的節點。

* 葉子節點：直接刪除。
* 單子節點：用子節點替換當前節點。
* 如果該節點有兩個子節點，則找到該節點在右子樹中找到目標節點的中序後繼節
點（或在左子樹中找到中序前驅節點），將中序後繼節點的值複製到目標節點，然
後遞迴地刪除中序後繼節點。

## 程式實作
所使用到的所有函式庫和namespace
```cpp
#include <iostream>
#include <random>
#include <cmath>
#include <utility>
#include <vector>
#include <chrono>
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
        int n = 10000;
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
        int key_to_delete = keys[gen() % n]; 
        auto start = chrono::high_resolution_clock::now();
        bst.Delete(key_to_delete);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        double delete_time_ms = duration / 1000.0; 

        int h = bst.getHeight();
        double ratio = (double)h / log2(n);
        cout << n << "," << h << "," << ratio << "," << delete_time_ms << endl;   
        return 0;
}
```

## 效能分析

### 時間精確度:us

### 各數值的比值表(10次取平均)
| 測試案例 | 輸入參數 $n$ | 高度 | 高度除以log2n比值| 
|----------|--------------|----------|----------|
| 測試一   | $n = 100$      | 13.8      |2.0772|
| 測試二   | $n = 500$      | 20.0	        | 2.2308     |
| 測試三   | $n = 1000$      | 20.9       | 2.0072       |
| 測試四   | $n = 2000$      |24.3	      | 2.1159     |
| 測試五   | $n = 3000$     | 26.2 |2.2683 | 
| 測試六   | $n = 10000$     |  31.6	|2.3781|  

根據上述表格可以看出總體比值大概都是為2開頭上下，高度符合O(log2)

| 測試案例 | 輸入參數 $n$ | 耗時(10次取平均| 
|----------|--------------|----------|
| 測試一   | $n = 100$      | 1     |
| 測試二   | $n = 500$      | 1	        | 
| 測試三   | $n = 1000$      | 1       | 
| 測試四   | $n = 2000$      |1      | 
| 測試五   | $n = 3000$     | 1 |
| 測試六   | $n = 10000$     |  2|

根據上述表格可以看出刪除的時間複雜度符合平均 O(log n)

## 測試與驗證

```c++
int n =10000;
```
更改main裡的這一行為想要的測試的資料量重複執行10次取得的插入後的高度和比值和執行隨機刪除其中一個key所需要的時間並都取平均記錄在表格上

### 計時方式
使用在<chrono>中的high_resolution_clock::now()，單位為毫秒
用法如以下程式
```c++
auto start = chrono::high_resolution_clock::now();
bst.Delete(key_to_delete);
auto end = chrono::high_resolution_clock::now();
auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
double delete_time_ms = duration / 1000.0; // 轉換為毫秒
```
### 結論
經過測試可以得知插入不同大小的資料量的高度都有有符合O(log2)而且在對應資料量大小的BST底下刪除任意一個key的時間也有符合平均 O(log n)





## 申論及開發報告





