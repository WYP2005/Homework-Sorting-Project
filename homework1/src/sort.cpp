#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

// insertion sort
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

// quick sort
template<class T>
vector<T> quicksort(vector<T> a, const int& front, const int& end){
    if(front >= end)
    {
        vector<T> result;
        result.push_back(a[front]);
        return result;
    }

    int mid = a[(front+end)/2], pivot;
    // 取三個數的中間值
    pivot = front;
    if((a[front] >= mid && mid >= a[end]) || (a[front] <= mid && mid <= a[end]))
        pivot = (front+end) / 2;
    if((a[end] >= a[front] && a[end] <= mid) || (a[end] <= a[front] && a[end] >= mid))
        pivot = end;

    // 將pivot移到最左邊
    swap(a[front], a[pivot]);

    // 將比pivot小的數移到左邊，比pivot大的數移到右邊
    int i = front, j = end + 1;
    do{
        do i++; while(a[i] < a[front]);
        do j--; while(a[j] > a[front]);
        if(i < j) swap(a[i], a[j]);
    }while(i < j);
    
    swap(a[front], a[j]);

    vector<T> left = quicksort(a, front, j - 1);   // 排序左邊
    vector<T> right = quicksort(a, j + 1, end);    // 排序右邊

    // 合併
    left.push_back(a[j]);
    left.insert(left.end(), right.begin(), right.end());
    return left;
}

// heap sort
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
vector<int> heapsort(vector<T> a){
    int len = a.size();
    maxheap(a);
    for(int i = a.size()-1; i > 0; i--){
        swap(a[i], a[0]);
        // 減掉以排序的長度在找下個最大堆積
        maxheapify(a, 0, --len);
    }
    return a;
}

// merge sort
// 將左右陣列合併並排列
template<class T>
vector<T> merge(const vector<T>& left, const vector<T>& right){
    vector<T> result;
    int i, j;
    i = j = 0;

    // 若左陣列和右邊界都還沒到底，繼續比較
    while(i < left.size() && j < right.size()){
        if(left[i] < right[j]){
            result.push_back(left[i]);
            i++;
        }
        else{
            result.push_back(right[j]);
            j++;
        }
    }

    // 將剩下的數值填入結果
    while(i < left.size())
        result.push_back(left[i++]);
    while(j < right.size())
        result.push_back(right[j++]);

    return result;
}

template<class T>
vector<T> mergesort(const vector<T>& a, const int& front, const int& end){
    // 只剩一個元素時，回傳單一元素的vector
    if(front == end)
    {
        vector<T> result;
        result.push_back(a[front]);
        return result;
    }
        
    int mid = (front+end) / 2;
    
    vector<T> left = mergesort(a, front, mid),
              right = mergesort(a, mid+1, end);

    // 合併並排列
    return merge(left, right);
}

// 檢查排序是否正確
template<class T>
bool checksort(const vector<T>& a, int n){
    for(int i = 0; i < n - 1; i++)
        if(a[i] > a[i+1]) return false;
    return true;
}

int main(){
    ifstream in;
    int n;
    in.open("data.txt");
    // 讀入資料筆數
    in >> n;
    vector<int> a(n), result;
    double start, stop;

    // 讀入資料
    for(int i = 0; i < n; i++)
        in >> a[i];
        
    // 測試插入排序
    start = clock();
    result = insertsort(a, n);
    stop = clock();
    if(checksort(result, n))
        cout << "insertsort time:" << (stop - start) / CLOCKS_PER_SEC << "s" << endl;

    // 測試快速排序
    start = clock();
    result = quicksort(a, 0, n - 1);
    stop = clock();
    if(checksort(result, n))
        cout << "quicksort time:" << (stop - start) / CLOCKS_PER_SEC << "s" << endl;
   
    // 測試整合排序
    start = clock();
    result = mergesort(a, 0, n - 1);
    stop = clock();
    if(checksort(result, n))
        cout << "mergesort time:" << (stop - start) / CLOCKS_PER_SEC << "s" << endl;

    // 測試堆積排序
    start = clock();
    result = heapsort(a);
    stop = clock();
    if(checksort(result, n))
        cout << "heapsort time:" << (stop - start) / CLOCKS_PER_SEC << "s" << endl;

    in.close();
}
