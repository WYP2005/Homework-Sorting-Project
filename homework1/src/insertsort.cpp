#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

template<class T>
void insertsort(T* a, int n){
    for(int i = 2; i <= n; i++){
        a[0] = a[i];
        int j = i - 1;
        while(j >= 1 && a[0] < a[j]){
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = a[0];
    }
}

bool checksort(int* a, int n){
    for(int i = 1; i < n; i++)
        if(a[i] > a[i+1]) return false;
    return true;
}

int main(){
    ifstream in;
    int n;
    in.open("data.txt");
    in >> n;
    int a[n+1];
    
    for(int i = 1; i < n; i++)
        in >> a[i];

    double start, stop;
    start = clock();
    insertsort(a, n);
    stop = clock();

    // for(int i = 1; i <= n; i++) cout << a[i] << " ";
    cout << checksort(a, n) << endl;
    cout << "執行時間:" << (stop - start) / CLOCKS_PER_SEC << "s" << endl;

    in.close();
}