#include <iostream>
#include <fstream>
#include <algorithm>

// 函式：生成 Merge Sort 最糟情況數據
void generateWorstCaseMergeSort(int left, int right, int* arr) {
    if (left == right) return;

    int mid = (left + right) / 2;

    int* temp = new int[right - left + 1];
    for (int i = left; i <= right; ++i) temp[i - left] = arr[i];

    for (int i = left, j = 0; i <= right; ++i, ++j) {
        if (j % 2 == 0)
            arr[i] = temp[j / 2];
        else
            arr[i] = temp[mid - left + 1 + j / 2];
    }

    delete[] temp;

    generateWorstCaseMergeSort(left, mid, arr);
    generateWorstCaseMergeSort(mid + 1, right, arr);
}

int main() {
    int n;
    std::cout << "請輸入數據大小 n: ";
    std::cin >> n;

    if (n <= 0) {
        std::cout << "數據大小必須為正整數！" << std::endl;
        return 1;
    }

    int* arr = new int[n];
    for (int i = 0; i < n; ++i) arr[i] = i + 1;

    generateWorstCaseMergeSort(0, n - 1, arr);

    std::ofstream outFile("data.txt");
    if (!outFile) {
        std::cerr << "無法創建或寫入文件！" << std::endl;
        delete[] arr;
        return 1;
    }

    // 在第一行寫入數據大小
    outFile << n << std::endl;

    // 在後續行中寫入實際數據
    for (int i = 0; i < n; ++i) outFile << arr[i] << " ";
    outFile << std::endl;
    outFile.close();

    std::cout << "數據已成功寫入 data.txt！" << std::endl;

    delete[] arr;
    return 0;
}
