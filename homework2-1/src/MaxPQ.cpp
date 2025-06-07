#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
class MaxPQ{
    public:
        virtual ~MaxPQ(){}
        virtual bool isEmpty() const = 0;
        virtual const T& Top() const = 0;
        virtual void Push(const T&) = 0;
        virtual void Pop() = 0;      
};

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