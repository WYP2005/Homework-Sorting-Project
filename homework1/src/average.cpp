#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

// 隨機排列生成器
template<class T>
void Permute(T* a, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(a[i], a[j]);
    }
}

// 插入排序（原始使用陣列）
template<class T>
void insertsortArray(T* a, int n) {
    for (int i = 2; i <= n; i++) {
        a[0] = a[i];
        int j = i - 1;
        while (j >= 1 && a[0] < a[j]) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = a[0];
    }
}

// 快速排序（原始使用 vector，中位數三分法）
template<class T>
void quicksort(vector<T>& a, int left, int right) {
    if (left < right) {
        int mid = a[(left + right) / 2], pivot = left;
        if ((a[left] >= mid && mid >= a[right]) || (a[left] <= mid && mid <= a[right]))
            pivot = (left + right) / 2;
        if ((a[right] >= a[left] && a[right] <= mid) || (a[right] <= a[left] && a[right] >= mid))
            pivot = right;

        swap(a[left], a[pivot]);
        int i = left, j = right + 1;
        do {
            do i++; while (i <= right && a[i] < a[left]);
            do j--; while (j >= left && a[j] > a[left]);
            if (i < j) swap(a[i], a[j]);
        } while (i < j);

        swap(a[left], a[j]);
        quicksort(a, left, j - 1);
        quicksort(a, j + 1, right);
    }
}

// 合併排序（原始使用 vector，遞迴版）
template<class T>
void merge(vector<T>& a, const int& front, const int& mid, const int& end) {
    int i = 0, j = 0, count = front;
    vector<T> left(a.begin() + front, a.begin() + mid + 1),
        right(a.begin() + mid + 1, a.begin() + end + 1);

    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) {
            a[count] = left[i];
            i++;
        }
        else {
            a[count] = right[j];
            j++;
        }
        count++;
    }

    while (i < left.size())
        a[count++] = left[i++];
    while (j < right.size())
        a[count++] = right[j++];
}

template<class T>
void mergesort(vector<T>& a, const int& front, const int& end) {
    if (front < end) {
        int mid = (front + end) / 2;
        mergesort(a, front, mid);
        mergesort(a, mid + 1, end);
        merge(a, front, mid, end);
    }
}

// 堆排序（第一個版本）
template<class T>
void maxheapify1(vector<T>& a, const int& root, const int& len) {
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
        maxheapify1(a, largest, len);
    }
}

template<class T>
void maxheap1(vector<T>& a) {
    for (int i = a.size() / 2; i >= 0; i--) {
        maxheapify1(a, i, a.size());
    }
}

template<class T>
void heapsort1(vector<T>& a) {
    int len = a.size();
    maxheap1(a);
    for (int i = a.size() - 1; i > 0; i--) {
        swap(a[i], a[0]);
        maxheapify1(a, 0, --len);
    }
}

// 第五個程式的堆排序與複合排序
template<class T>
void maxheapify2(vector<T>& a, const int& root, const int& len) {
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
        maxheapify2(a, largest, len);
    }
}

template<class T>
void maxheap2(vector<T>& a, const int& left, const int& right) {
    int size = right - left + 1;
    for (int i = size; i >= left; i--) {
        maxheapify2(a, i, size);
    }
}

template<class T>
void heapsort2(vector<T>& a, const int& left, const int& right) {
    int size = right - left + 1;
    maxheap2(a, left, right);
    for (int i = right; i > left; i--) {
        swap(a[i], a[left]);
        maxheapify2(a, left, --size);
    }
}

template<class T>
void insertsortVector(vector<T>& a, const int& left, const int& right) {
    T temp;
    for (int i = left + 1; i <= right; i++) {
        temp = a[i];
        int j = i - 1;
        while (j >= left && temp < a[j]) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = temp;
    }
}

template<class T>
void compositesort(vector<T>& a, const int& left, const int& right, int& depth) {
    int size = right - left + 1;

    if (left >= right) return;

    if (size <= 32) {
        insertsortVector(a, left, right);
        return;
    }

    if (depth >= 1000) {
        heapsort2(a, left, right);
        return;
    }

    int mid = a[(left + right) / 2], pivot = left;
    if ((a[left] >= mid && mid >= a[right]) || (a[left] <= mid && mid <= a[right]))
        pivot = (left + right) / 2;
    if ((a[right] >= a[left] && a[right] <= mid) || (a[right] <= a[left] && a[right] >= mid))
        pivot = right;

    swap(a[left], a[pivot]);
    int i = left, j = right + 1;
    do {
        do i++; while (i <= right && a[i] < a[left]);
        do j--; while (j >= left && a[j] > a[left]);
        if (i < j) swap(a[i], a[j]);
    } while (i < j);

    swap(a[left], a[j]);

    depth++;
    compositesort(a, left, j - 1, depth);
    compositesort(a, j + 1, right, depth);
}

// 檢查排序正確性
bool checksortArray(int* a, int n) {
    for (int i = 1; i < n; i++)
        if (a[i] > a[i + 1]) return false;
    return true;
}

template<class T>
bool checksortVector(vector<T>& a, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1]) return false;
    }
    return true;
}

// 測量平均情況運行時間
double measureAverageTimeInsertArray(int n, int numPerms) {
    vector<int*> permutations(numPerms);
    for (int p = 0; p < numPerms; p++) {
        permutations[p] = new int[n + 1];
        for (int j = 1; j <= n; j++) {
            permutations[p][j] = j;
        }
        Permute(permutations[p] + 1, n);
    }

    double start = clock();
    for (int p = 0; p < numPerms; p++) {
        int* copy = new int[n + 1];
        for (int j = 0; j <= n; j++) copy[j] = permutations[p][j];
        insertsortArray(copy, n);
        delete[] copy;
    }
    double stop = clock();

    for (int p = 0; p < numPerms; p++) delete[] permutations[p];
    return (stop - start) / (double)CLOCKS_PER_SEC / numPerms;
}

double measureAverageTimeVector(int n, int numPerms, void (*sortFunc)(vector<int>&)) {
    vector<vector<int>> permutations(numPerms, vector<int>(n));
    for (int p = 0; p < numPerms; p++) {
        for (int j = 0; j < n; j++) {
            permutations[p][j] = j + 1;
        }
        Permute(permutations[p].data(), n);
    }

    double start = clock();
    for (int p = 0; p < numPerms; p++) {
        vector<int> copy = permutations[p];
        sortFunc(copy);
    }
    double stop = clock();

    return (stop - start) / (double)CLOCKS_PER_SEC / numPerms;
}

double measureAverageTimeComposite(int n, int numPerms) {
    vector<vector<int>> permutations(numPerms, vector<int>(n));
    for (int p = 0; p < numPerms; p++) {
        for (int j = 0; j < n; j++) {
            permutations[p][j] = j + 1;
        }
        Permute(permutations[p].data(), n);
    }

    double start = clock();
    for (int p = 0; p < numPerms; p++) {
        vector<int> copy = permutations[p];
        int depth = 0;
        compositesort(copy, 0, n - 1, depth);
    }
    double stop = clock();

    return (stop - start) / (double)CLOCKS_PER_SEC / numPerms;
}

int main() {
    int numPerms = 50;
    int n_values[] = { 500, 1000, 2000, 3000, 4000, 5000 };

    srand(static_cast<unsigned>(time(0)));

    cout << "平均情況運行時間測試 (基於 " << numPerms << " 個隨機排列):\n";
    for (int n : n_values) {
        cout << "n = " << n << ":\n";

        // 插入排序（陣列版）
        double insertTimeArray = measureAverageTimeInsertArray(n, numPerms);
        int* testInsertArray = new int[n + 1];
        for (int i = 1; i <= n; i++) testInsertArray[i] = i;
        Permute(testInsertArray + 1, n);
        insertsortArray(testInsertArray, n);
        cout << "  插入排序(陣列): " << insertTimeArray << " 秒, 正確性: " << (checksortArray(testInsertArray, n + 1) ? "Yes" : "No") << endl;
        delete[] testInsertArray;

        // 快速排序
        double quickTime = measureAverageTimeVector(n, numPerms, [](vector<int>& a) { quicksort(a, 0, a.size() - 1); });
        vector<int> testQuick(n);
        for (int i = 0; i < n; i++) testQuick[i] = i + 1;
        Permute(testQuick.data(), n);
        quicksort(testQuick, 0, n - 1);
        cout << "  快速排序: " << quickTime << " 秒, 正確性: " << (checksortVector(testQuick, n) ? "Yes" : "No") << endl;

        // 合併排序
        double mergeTime = measureAverageTimeVector(n, numPerms, [](vector<int>& a) { mergesort(a, 0, a.size() - 1); });
        vector<int> testMerge(n);
        for (int i = 0; i < n; i++) testMerge[i] = i + 1;
        Permute(testMerge.data(), n);
        mergesort(testMerge, 0, n - 1);
        cout << "  合併排序: " << mergeTime << " 秒, 正確性: " << (checksortVector(testMerge, n) ? "Yes" : "No") << endl;

        // 堆排序（第一個版本）
        double heapTime1 = measureAverageTimeVector(n, numPerms, heapsort1);
        vector<int> testHeap1(n);
        for (int i = 0; i < n; i++) testHeap1[i] = i + 1;
        Permute(testHeap1.data(), n);
        heapsort1(testHeap1);
        cout << "  堆排序(第一版): " << heapTime1 << " 秒, 正確性: " << (checksortVector(testHeap1, n) ? "Yes" : "No") << endl;

        // 複合排序
        double compositeTime = measureAverageTimeComposite(n, numPerms);
        vector<int> testComposite(n);
        for (int i = 0; i < n; i++) testComposite[i] = i + 1;
        Permute(testComposite.data(), n);
        int depth = 0;
        compositesort(testComposite, 0, n - 1, depth);
        cout << "  複合排序: " << compositeTime << " 秒, 正確性: " << (checksortVector(testComposite, n) ? "Yes" : "No") << endl;

        cout << endl;
    }

    cout << "測試完成\n";
    return 0;
}
