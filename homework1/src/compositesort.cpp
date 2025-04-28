#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;


template<class T>
void maxheapify(vector<T>& a, const int& root, const int& left, const int& right){
    int l = 2 * root + 1; // left child
    int r = 2 * root + 2; // right child
    int largest = root;

    // 如果左子樹存在且大於根節點
    if (l <= right && l >= left && a[l] > a[largest]) {
        largest = l;
    }

    // 如果右子樹存在且大於根節點
    if (r <= right && r >= left && a[r] > a[largest]) {
        largest = r;
    }

    // 如果最大值不是根節點，則交換並遞迴調整
    if (largest != root) {
        swap(a[root], a[largest]);
        maxheapify(a, largest, left, right);
    }
}

// 建立最大堆積樹
template<class T>
void maxheap(vector<T>& a, const int& left, const int& right){
    int size = right - left + 1;
    for (int i = (right - 1) / 2; i >= left; i--) {
        maxheapify(a, i, left, right);
    }
}

template<class T>
vector<T> heapsort(vector<T> a, const int& left, const int& right){
    int size = right - left + 1;
    maxheap(a, left, right); // 建立最大堆積
    for (int i = right; i > left; i--) {
        // 將當前最大元素交換到右邊
        swap(a[left], a[i]);
        // 再次調整堆積
        maxheapify(a, left, left, i - 1);
    }
    return a;
}

template<class T>
vector<T> insertsort(vector<T> a, const int& left, const int& right){
    T temp;
    for(int i = left + 1; i <= right; i++){
        temp = a[i];
        int j = i - 1;
        while(j >= left && temp < a[j]){
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = temp;
    }
    return a;
}

template<class T>
void compositesort(vector<T>& a, const int& left, const int& right, int& depth) {
    int size = right - left + 1;

    if (left >= right) return;

    // // 小數據使用insertSort
    if (size <= 30) {
        a = insertsort(a, left, right);
        return;
    }

    // 遞迴深度過深用heapSort
    if(depth >= 1000){
        a = heapsort(a, left, right);
        return;
    }

    // 預設使用quickSort
    // 取三個數的中間值
    int mid = a[(left+right)/2], pivot = left;
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

    compositesort(a, left, j - 1, ++depth);
    compositesort(a, j + 1, right, ++depth);
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
    int n, depth = 100;
    in.open("data.txt");
    in >> n;
    vector<int> test(n);
    for(int i = 0; i < n; i++){
        in >> test[i];
    }

    double start, stop;
    start = clock();
    compositesort(test, 0, n - 1, depth);
    stop = clock();

    if(checksort(test, n))
        cout << (stop - start) / CLOCKS_PER_SEC<< endl;

    in.close();
}