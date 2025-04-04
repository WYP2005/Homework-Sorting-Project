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