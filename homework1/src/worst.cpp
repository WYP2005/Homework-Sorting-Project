#include <iostream>
#include <Windows.h>
#include <Psapi.h>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

void memoryUsage(){
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"Memory Usage Information:" << endl;
    cout<<"Working Set Size: "<<pmc.WorkingSetSize / 1024 << " KB" << endl;
    cout<<"Peak Working Set Size: "<<pmc.PeakWorkingSetSize / 1024 << " KB" << endl;
    cout<<"Pagefile Usage: "<<pmc.PagefileUsage / 1024 << " KB" << endl;
    cout<<"----------------------------------------------------------"<<endl;
}

vector<int> read_data(const string& filename, int& n) {
    ifstream in;
    in.open(filename);
    if (!in.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    // 讀入資料筆數
    in >> n;
    vector<int> a(n);

    // 讀入資料
    for (int i = 0; i < n; i++) {
        if (!(in >> a[i])) {
            in.close();
            throw runtime_error("Invalid data format in file: " + filename);
        }
    }

    in.close();
    return a;
}

// Function to write data to file in the required format
void write_to_file(const vector<int>& data, const string& filename) {
    ofstream out(filename);
    out << data.size() << endl;
    for (int i = 0; i < data.size(); i++) {
        out << data[i];
        if (i < data.size() - 1) out << " ";
    }
    out << endl;
    out.close();
}

// Permute function to generate random permutation
void permute(vector<int>& arr, int n) {
    for (int i = n - 1; i >= 1; --i) {
        int j = rand() % (i + 1); // Random index from 0 to i
        swap(arr[i], arr[j]);
    }
}

// Insertion Sort worst-case: [n, n-1, ..., 1]
void generate_insertion_worst(int n) {
    vector<int> data(n);
    for (int i = 0; i < n; i++) {
        data[i] = n - i;
    }
    write_to_file(data, "data.txt");
}

// Generate random permutation for Merge Sort
void generate_merge_worst(int n) {
    srand(time(0));
    vector<int> arr(n);

    // Initialize array with 1 to n
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }

    // Generate one random permutation
    permute(arr, n);
    write_to_file(arr, "data.txt");
}

// Generate random permutation for Heap Sort
void generate_heap_worst(int n) {
    srand(time(0));
    vector<int> arr(n);

    // Initialize array with 1 to n
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }

    // Generate one random permutation
    permute(arr, n);
    write_to_file(arr, "data.txt");
}

void generate_random_data(int n) {
    ofstream out("data.txt");
    if (!out.is_open()) {
        cerr << "無法開啟檔案: " << "data.txt" << endl;
        return;
    }

    srand(time(NULL)); // 設定隨機種子

    out << n << endl; // 寫入資料筆數
    for (int i = 0; i < n; i++) {
        out << rand() % n << " ";
    }
    out << endl;

    out.close();
}

// insertion sort
template<class T>
vector<T> insertsort(vector<T> a, int n) {
    T temp;
    for (int i = 1; i < n; i++) {
        temp = a[i];
        int j = i - 1;
        while (j >= 0 && temp < a[j]) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = temp;
    }
    return a;
}

// quick sort
template<class T>
void quicksortWorst(vector<T>& a, const int& front, const int& end) {
    if (front < end) {
        int mid = a[(front + end) / 2], pivot;
        // 取三個數的最大值
        pivot = front;
        if (mid >= a[front] && mid >= a[end])
            pivot = (front + end) / 2;
        if ((a[end] >= a[front] && a[end] >= mid))
            pivot = end;

        // 將pivot移到最左邊
        swap(a[front], a[pivot]);

        // 將比pivot小的數移到左邊，比pivot大的數移到右邊
        int i = front, j = end + 1;
        do {
            do i++; while (a[i] < a[front]);
            do j--; while (a[j] > a[front]);
            if (i < j) swap(a[i], a[j]);
        } while (i < j);
        swap(a[front], a[j]);

        quicksortWorst(a, front, j - 1); // 對左邊的數進行排序
        quicksortWorst(a, j + 1, end);   // 對右邊的數進行排序
    }
}

// quick sort
template<class T>
void quicksortNormal(vector<T>& a, const int& front, const int& end) {
    if (front < end) {
        int mid = a[(front + end) / 2], pivot;
        // 取三個數的最大值
        pivot = front;
        if((a[front] >= mid && mid >= a[end]) || (a[front] <= mid && mid <= a[end]))
            pivot = (front+end) / 2;
        if((a[end] >= a[front] && a[end] <= mid) || (a[end] <= a[front] && a[end] >= mid))
            pivot = end;

        // 將pivot移到最左邊
        swap(a[front], a[pivot]);

        // 將比pivot小的數移到左邊，比pivot大的數移到右邊
        int i = front, j = end + 1;
        do {
            do i++; while (a[i] < a[front]);
            do j--; while (a[j] > a[front]);
            if (i < j) swap(a[i], a[j]);
        } while (i < j);
        swap(a[front], a[j]);

        quicksortNormal(a, front, j - 1); // 對左邊的數進行排序
        quicksortNormal(a, j + 1, end);   // 對右邊的數進行排序
    }
}
template<class T>
vector<T> quicksort(vector<T> a, const int& front, const int& end, const bool& worst) {
    if(worst)
        quicksortWorst(a, front, end);
    else
        quicksortNormal(a, front, end);
    return a;
}

// heap sort
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

// 建立最大堆積樹
template<class T>
void maxheap(vector<T>& a) {
    for (int i = a.size() / 2; i >= 0; i--) {
        maxheapify(a, i, a.size());
    }
}

template<class T>
vector<int> heapsort(vector<T> a) {
    int len = a.size();
    maxheap(a);
    for (int i = a.size() - 1; i > 0; i--) {
        swap(a[i], a[0]);
        // 減掉以排序的長度在找下個最大堆積
        maxheapify(a, 0, --len);
    }
    return a;
}

// merge sort
// 將左右陣列合併並排列
template<class T>
vector<T> merge(const vector<T>& left, const vector<T>& right) {
    vector<T> result;
    int i, j;
    i = j = 0;

    // 若左陣列和右邊界都還沒到底，繼續比較
    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) {
            result.push_back(left[i]);
            i++;
        }
        else {
            result.push_back(right[j]);
            j++;
        }
    }

    // 將剩下的數值填入結果
    while (i < left.size())
        result.push_back(left[i++]);
    while (j < right.size())
        result.push_back(right[j++]);

    return result;
}

template<class T>
vector<T> mergesort(const vector<T>& a, const int& front, const int& end) {
    // 只剩一個元素時，回傳單一元素的vector
    if (front == end)
    {
        vector<T> result;
        result.push_back(a[front]);
        return result;
    }

    int mid = (front + end) / 2;

    vector<T> left = mergesort(a, front, mid),
        right = mergesort(a, mid + 1, end);

    // 合併並排列
    return merge(left, right);
}

// 檢查排序是否正確
template<class T>
bool checksort(const vector<T>& a, int n) {
    for (int i = 0; i < n - 1; i++)
        if (a[i] > a[i + 1]) return false;
    return true;
}

template<class T>
void compositesort(vector<T> a, const int& left, const int& right, int& depth) {
    int size = right - left + 1;

    if (left >= right){
        vector<T> result;
        result.push_back(a[left]);
        return result;
    }

    // 小數據使用insertSort
    if (size <= 30) {
        a = insertsort(a, left, right);
        return;
    }

    // 遞迴深度過深用heapSort
    if(depth >= 1000){
        a = heapsort(a, left, right);
        return;
    }

    // 預設使用quickSort
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

    compositesort(a, left, j - 1, ++depth);
    compositesort(a, j + 1, right, ++depth);
}

int main() {

    // 最糟狀況
    int data = 10000;
    int n;
    vector<int> result;
    double start, stop;
    vector<int> a = read_data("data.txt", n);

    // 測試插入排序
    // generate_insertion_worst(data);
    // a = read_data("data.txt", n);
    // double time = 0, count = 0;
    // memoryUsage();
    // for (int i = 0; i < 55; i++) {
    //     start = clock();
    //     result = insertsort(a, n);
    //     stop = clock();
    //     if (checksort(result, n)) {
    //         time += (stop - start) / CLOCKS_PER_SEC;
    //         count++;
    //     }
    // }
    // memoryUsage();
    // std::cout << "insertsort time:" << time / count << "s" << endl;

    // // 測試快速排序
    // // generate_quick_worst(data);
    // a = read_data("data.txt", n);
    // time = 0, count = 0;
    // for (int i = 0; i < 55; i++) {
    //     start = clock();
    //     result = quicksort(a, 0, n - 1, true);
    //     stop = clock();
    //     if (checksort(result, n)) {
    //         time += (stop - start) / CLOCKS_PER_SEC;
    //         count++;
    //     }
    // }
    // memoryUsage();
    // std::cout << "quicksort time:" << time / count << "s" << endl;

    // // 測試整合排序
    // double max_time = 0;
    // for (int i = 0; i < 20; i++) {
    //     generate_merge_worst(data);
    //     a = read_data("data.txt", n);
    //     start = clock();
    //     result = mergesort(a, 0, n - 1);
    //     stop = clock();
    //     if (checksort(result, n)) {
    //         if (((stop - start) / CLOCKS_PER_SEC) > max_time) {
    //             max_time = (stop - start) / CLOCKS_PER_SEC;
    //         }
    //     }
    // }
    // memoryUsage();
    // std::cout << "mergesort time:" << max_time << "s" << endl;

    // // 測試堆積排序
    // max_time = 0;
    // for (int i = 0; i < 20; i++) {
    //     generate_heap_worst(data);
    //     a = read_data("data.txt", n);
    //     start = clock();
    //     result = heapsort(a);
    //     stop = clock();
    //     if (checksort(result, n)) {
    //         if (((stop - start) / CLOCKS_PER_SEC) > max_time) {
    //             max_time = (stop - start) / CLOCKS_PER_SEC;
    //         }
    //     }
    // }
    // memoryUsage();
    // std::cout << "heapsort time:" << max_time << "s" << endl;

    // 平均狀況      
    double time2 = 0, count2 = 0;
    double time3 = 0, count3 = 0;
    double time4 = 0, count4 = 0;
    double time5 = 0,count5= 0;
	double time6 = 0, count6 = 0;
    for (int i = 0; i < 20; i++) {
        generate_random_data(data);
        a = read_data("data.txt", n);
        start = clock();
        result = insertsort(a, n);
        stop = clock();
        if (checksort(result, n)) {
            time2 += (stop - start) / CLOCKS_PER_SEC;
            count2++;
        }
        start = clock();
        result = quicksort(a, 0, n - 1, false);
        stop = clock();
        if (checksort(result, n)) {
            time3 += (stop - start) / CLOCKS_PER_SEC;
            count3++;
        }
        start = clock();
        result = mergesort(a, 0, n - 1);
        stop = clock();
        if (checksort(result, n)) {
            time4 += (stop - start) / CLOCKS_PER_SEC;
            count4++;
        }
        start = clock();
        result = heapsort(a);
        stop = clock();
        if (checksort(result, n)) {
            time5 += (stop - start) / CLOCKS_PER_SEC;
            count5++;
        }
    }
    std::cout << "insertsort time:" << time2 / count2 << "s" << endl;
    std::cout << "quicksort time:" << time3 / count3 << "s" << endl;
    std::cout << "mergesort time:" << time4 / count4 << "s" << endl;
    std::cout << "heapsort time:" << time5 / count5 << "s" << endl;
    
}
