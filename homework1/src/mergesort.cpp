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