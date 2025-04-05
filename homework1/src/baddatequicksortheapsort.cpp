#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

// 調整後的隨機排列生成器（0 基索引）
template<class T>
void Permute(T* a, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1); // j = random integer in the range [0, i]
        swap(a[i], a[j]);
    }
}

void generateWorstCasePermutation(int n, ofstream& outfile, const int label) {
    outfile << label << "\n";
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;     // 填充 1 到 n
    }
    Permute(arr.data(), n); // 使用調整後的 Permute 生成單一隨機排列
    for (int num : arr) {
        outfile << num << " ";
    }
    outfile << "\n\n";
}

int main() {
    int n;

    cout << "請輸入數據規模 n: ";
    cin >> n;

    srand(static_cast<unsigned>(time(0)));

    ofstream outfile("data.txt");
    if (!outfile.is_open()) {
        cerr << "無法開啟檔案 data.txt\n";
        return 1;
    }

    generateWorstCasePermutation(n, outfile, n);
    

    outfile.close();
    cout << "最糟情況資料已生成並寫入 data.txt\n";
    return 0;
}
