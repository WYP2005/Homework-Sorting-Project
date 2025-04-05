#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
using namespace std;

template<class T>
void quicksort(vector<T>& a, int left, int right){
    if(left < right){
        int mid = a[(left+right)/2], pivot;

        // 取三個數的中間值
        pivot = left;
        // if((a[left] >= mid && mid >= a[right]) || (a[left] <= mid && mid <= a[right]))
        //     pivot = (left+right) / 2;
        // if((a[right] >= a[left] && a[right] <= mid) || (a[right] <= a[left] && a[right] >= mid))
        //     pivot = right;

        // 將pivot移到最左邊
        swap(a[left], a[pivot]);
        int i = left, j = right + 1;
        do{
            do i++; while(a[i] < a[left]);
            do j--; while(a[j] > a[left]);
            if(i < j) swap(a[i], a[j]);
        }while(i < j);
        
        swap(a[left], a[j]);
        
        quicksort(a, left, j - 1);
        quicksort(a, j + 1, right);
    }

}

template<class T>
bool checksort(vector<T>& a, int n){
    for(int i = 0; i < n - 1; i++)
        if(a[i] > a[i+1]) return false;
    return true;
}

int main(){
    ifstream in;
    int n;
    in.open("data.txt");
    in >> n;
    vector<int> a(n);
    
    double start, stop;
    for(int i = 0; i < n; i++)
        in >> a[i];

    start = clock();
    quicksort(a, 0, n - 1);
    stop = clock();

    // for(int i = 0; i < n; i++) cout << a[i] << " ";
    // cout << endl;
    cout << checksort(a, n) << endl;
    cout << "執行時間:" << (stop - start) / CLOCKS_PER_SEC << endl;
   
    in.close();
}
