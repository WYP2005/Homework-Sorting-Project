#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>
using namespace std;

int main(){
    ofstream out;
    int n, min, max;
    out.open("data.txt");
    srand(time(NULL));
    
    cout << "資料筆數:";
    cin >> n;
    // cout << "下限:";
    // cin >> min;
    // cout << "上限:";
    // cin >> max;

    out << n << " ";
    // 一般打亂
    // for(int i = 0; i < n; i++){
    //     out << rand()%(max-min+1) << " ";
    // }

    // insertion sort最耗時
    for(int i = n; i > 0; i--){
        out << i << " ";
    }
    
    out.close();
}