# 41243210
# 41243231

作業2-1

## 解題說明
實作最大/最小堆積

### 解題策略
#### 1. 類別MaxPQ、MinPQ定義虛擬函式
#### 2. 將MaxHeap、MinHeap繼承MaxPQ、MinPQ
#### 3. 實作虛擬函式、新增函式
#### Top函式
目的: 回傳最頂端的元素
1. 檢查Heap是否為空
2. 回傳最頂端的元素
#### Push函式
目的:將新元素加入Heap
1. 檢查容量是否足夠
2. 將新元素暫時插入在堆的最後位置
3. 向上調整
#### Pop函式
目的:移除頂端元素
1. 檢查Heap是否為空
2. 刪除最頂端的元素
3. 取出最後一個元素
4. 從根節點向下調整

## 程式實作
函式庫
```cpp
#include <iostream>
#include <algorithm>
```
MaxPQ/MinPQ類別，因MaxPQ和MinPQ所定義的虛函數一樣，故只取其一展示
```cpp
template <class T>
class MaxPQ{
    public:
        virtual ~MaxPQ(){}
        virtual bool isEmpty() const = 0;
        virtual const T& Top() const = 0;
        virtual void Push(const T&) = 0;
        virtual void Pop() = 0;      
};
```
MaxHeap類別
```cpp
template <class T>
class MaxHeap : MaxPQ<T> {
    private:
        T *heap;
        int heapSize;
        int capacity;

    public:
        MaxHeap(int theCapacity = 10){
           if(theCapacity < 1) throw "Capacity must be >= 1";
           capacity = theCapacity;
           heapSize = 0;
           heap = new T[capacity + 1];
        }
        ~MaxHeap() {
            delete[] heap;
        }

        void changeSize(T*& old, int oldSize, int newSize){
            T* newHeap = new T[newSize + 1];
            copy(old, old + oldSize + 1, newHeap);
            delete[] old;
            old = newHeap;
        }

        bool isEmpty() const {
            if(heapSize == 0)
                return true;
            return false;
        }

        const T& Top() const{
            if (heapSize == 0) {
                throw "Heap is empty";
            }
            return heap[1];
        }

        void Push(const T& value){
            if(heapSize == capacity) {
                changeSize(heap, capacity, 2 * capacity);
                capacity *= 2;
            }
            int currentNode = ++heapSize;
            while(currentNode != 1 && heap[currentNode/2] < value){
                heap[currentNode] = heap[currentNode/2];
                currentNode /= 2;
            }
            heap[currentNode] = value;
        }

        void Pop() {
            if(isEmpty()) throw "Heap is empty";
            heap[1].~T();

            T lastE = heap[heapSize--];

            int currentNode = 1; // root
            int child = 2;
            while(child <= heapSize){
                // 選擇當前父節點較大的子節點
                if(child < heapSize && heap[child] < heap[child + 1]) child++;
                
                // lastE已經小於當前子節點，不需要繼續下移
                if(lastE >= heap[child]) break;

                // lastE大於當前子節點，將子節點上移
                heap[currentNode] = heap[child];
                currentNode = child;
                child *= 2;
            }
            heap[currentNode] = lastE;
        }
};
```
MaxHeap和MinHeap差異
push函式 
```cpp
while(currentNode != 1 && heap[currentNode/2] > value){
    heap[currentNode] = heap[currentNode/2];
    currentNode /= 2;
}
```
pop函式 
```cpp
if(child < heapSize && heap[child] > heap[child + 1]) child++;
if(lastE <= heap[child]) break;
```

主程式實作
```cpp
int main(void){
    MaxHeap<int> maxHeap(5);
    maxHeap.Push(10);
    cout << maxHeap.Top() << endl;
    maxHeap.Push(5);
    cout << maxHeap.Top() << endl;
    maxHeap.Pop();
    cout << maxHeap.Top() << endl;
    maxHeap.Push(3);
    cout << maxHeap.Top() << endl;

    return 0;
}
```


## 效能分析
時間複雜度:  
Push() O($logN$)  
Pop()  O($logN$)  
Top()  O($1$)  
空間複雜度: $O(N)$
## 測試與驗證
以Max Heap作為演示
| 指令 | 最頂端值  
|----------|-----|
| Push(10) |  10 |
| Push(5)  |  10 |
| Pop()    |  5  |   
| Push(3)  |  5  |  

## 申論及開發報告
此次實作的Max/Min Heap可以在新增、移除、獲取最大/最小值上有著不錯的效能  
新增資料能保持資料排序，時間複雜度$O(logn)$  
獲取最大、最小值也只需要$O(1)$就可以達成  
空間方面基本上只有用到儲存數值的陣列n+1個空間

此次的實作讓我們了解Max/Min Heap的實作方式、效率，以幫助我們在之後可以運用。


