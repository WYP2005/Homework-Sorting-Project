#include <iostream>
#include <fstream>
using namespace std;

int main() {
    int n;
    cout << "請輸入 n: ";
    cin >> n;

    ofstream out("data.txt");
    if (!out) {
        cerr << "無法開啟 data.txt" << endl;
        return 1;
    }

    out << n << endl;
    for (int i = n; i >= 1; i--) {
        out << i << " ";
    }

    out.close();
    cout << "已生成最糟插入排序測資 (降序排列) 並寫入 data.txt" << endl;

    return 0;
}
