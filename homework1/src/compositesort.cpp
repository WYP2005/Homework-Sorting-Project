#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

template<class T>
void insertsort(vector<T>& a, const int& left, const int& right){
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
}

template<class T>
void compositesort(vector<T>& a, const int& left, const int& right) {
    int size = right - left + 1;

    if (left >= right) return;

    if (size <= 32) {
        insertsort(a, left, right);
        return;
    }

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

    compositesort(a, left, j - 1);
    compositesort(a, j + 1, right);
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
    compositesort(test, 0, n - 1);
    stop = clock();

    // for(int i = 0; i < n; i++) cout << test[i] << " ";
    // cout << endl;
    cout << checksort(test, n) << endl;
    cout << (stop - start) / CLOCKS_PER_SEC<< endl;

    in.close();
}