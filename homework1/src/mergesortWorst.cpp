#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>
using namespace std;


void generateWorstTimeData(int a[], const int& left, const int& right){
    if(left < right){
        int temp[right - left + 1];
        int index = 0;

        // 交錯
        for(int i = left; i <= right; i+=2)
            temp[index++] = a[i];
        for(int i = left+1; i <= right; i+=2)
            temp[index++] = a[i];

        // 覆蓋原陣列
        for(int i = left; i <= right; i++)
            a[i] = temp[i - left];
        
        // 只剩兩個元素就交換
        if((right - left) == 1) swap(a[left], a[right]);

        generateWorstTimeData(a, left, (left+right)/2);
        generateWorstTimeData(a, (left+right)/2+1, right);

    }
}

int main(){
    ofstream out;
    int n, min, max;
    out.open("data.txt");
    srand(time(NULL));
    
    cout << "資料筆數:";
    cin >> n;
    out << n << " ";

    int a[n];
    for(int i = 0; i < n; i++) a[i] = i;
    generateWorstTimeData(a, 0, n - 1);
    
    for(int i = 0; i < n; i++) out << a[i] << " ";
    out.close();
}