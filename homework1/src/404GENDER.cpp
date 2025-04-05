#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string> // 新增此頭文件以使用 getline
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

// 生成單一隨機排列並寫入文件（僅用於展示）
void generateWorstCasePermutation(int n, ofstream& outfile, const string& label) {
    outfile << label << " (Sample Permutation):\n";
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;     // 填充 1 到 n
    }
    Permute(arr.data(), n); // 生成單一隨機排列
    for (int num : arr) {
        outfile << num << " ";
    }
    outfile << "\n\n";
}

// 堆排序相關函數
template<class T>
void maxheapify(vector<T>& a, const int& root, const int& len) {
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    int largest = root;

    if (left < len && a[left] >= a[largest]) {
        largest = left;
    }

    if (right < len && a[right] >= a[largest]) {
        largest = right;
    }

    if (largest != root) {
        swap(a[root], a[largest]);
        maxheapify(a, largest, len);
    }
}

template<class T>
void maxheap(vector<T>& a) {
    for (int i = a.size() / 2; i >= 0; i--) {
        maxheapify(a, i, a.size());
    }
}

template<class T>
void heapsort(vector<T>& a) {
    int len = a.size();
    maxheap(a);
    for (int i = a.size() - 1; i > 0; i--) {
        swap(a[i], a[0]);
        maxheapify(a, 0, --len);
    }
}

template<class T>
bool checksort(vector<T>& a, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1]) return false;
    }
    return true;
}

// 測量單次堆排序時間
double measureHeapTime(vector<int>& arr) {
    double start = clock();
    heapsort(arr);
    double stop = clock();
    return (stop - start) / CLOCKS_PER_SEC; // 返回秒
}

// 生成多組隨機排列並取最大時間
double getMaxHeapTime(int n, int numPerms) {
    double maxTime = 0;
    for (int i = 0; i < numPerms; i++) {
        vector<int> arr(n);
        for (int j = 0; j < n; j++) {
            arr[j] = j + 1; // 填充 1 到 n
        }
        Permute(arr.data(), n); // 生成隨機排列
        vector<int> copy = arr; // 複製以保持原始資料
        double time = measureHeapTime(copy);
        maxTime = max(maxTime, time);
    }
    return maxTime;
}

int main() {
    int n, numPerms = 500; // 預設 10 組排列，符合作業要求

    // 讓使用者輸入數據規模
    cout << "請輸入數據規模 n: ";
    cin >> n;

    // 設置隨機數種子
    srand(static_cast<unsigned>(time(0)));

    // 生成單一隨機排列並寫入檔案（僅展示用）
    ofstream outfile("data.txt");
    if (!outfile.is_open()) {
        cerr << "無法開啟檔案 data.txt 進行寫入\n";
        return 1;
    }
    generateWorstCasePermutation(n, outfile, "Heap Sort Worst Case");
    outfile.close();

    // 從檔案讀取資料並測試單一排列
    ifstream infile("data.txt");
    if (!infile.is_open()) {
        cerr << "無法開啟檔案 data.txt 進行讀取\n";
        return 1;
    }

    string label;
    getline(infile, label); // 讀取標籤行
    vector<int> test(n);
    for (int i = 0; i < n; i++) {
        infile >> test[i];
    }
    infile.close();

    // 測試單一排列的堆排序
    vector<int> testCopy = test; // 複製以保持原始資料
    double singleTime = measureHeapTime(testCopy);
    cout << "單一隨機排列排序是否正確: " << (checksort(testCopy, n) ? "Yes" : "No") << endl;
    cout << "單一隨機排列執行時間: " << singleTime << " 秒" << endl;

    // 測試多組隨機排列並取最大時間
    double maxHeapTime = getMaxHeapTime(n, numPerms);
    cout << "多組隨機排列中最糟情況執行時間 (取 " << numPerms << " 組最大值): " << maxHeapTime << " 秒" << endl;

    cout << "最糟情況資料已生成並測試完成，樣本資料已寫入 data.txt\n";
    return 0;
}
