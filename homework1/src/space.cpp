#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <algorithm>
using namespace std;

size_t max_memory_usage = 0;

// 取得當前記憶體使用量
template<class T>
size_t memory_of_vector(const vector<T>& v) {
    return v.capacity() * sizeof(T);
}

// 更新最大記憶體使用量
void update_max_memory(size_t memory) {
    if (memory > max_memory_usage) {
        max_memory_usage = memory;
    }
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

    // 更新最大記憶體使用量
    update_max_memory(sizeof(temp));

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
void quicksortWorst(vector<T>& a, const int& front, const int& end, int depth) {
    if (front < end) {
        // 更新最大記憶體使用量
        update_max_memory(depth * 2 * sizeof(int));

        // 取三個數的最大值
        int mid = (front + end) / 2;
        if (a[mid] < a[front]) swap(a[front], a[mid]);
        if (a[end] < a[front]) swap(a[front], a[end]);
        if (a[mid] < a[end]) swap(a[mid], a[end]);
        // 將pivot移到最左邊
        swap(a[front], a[end]);

        // 將比pivot小的數移到左邊，比pivot大的數移到右邊
        int i = front, j = end + 1;
        do {
            do i++; while (a[i] < a[front]);
            do j--; while (a[j] > a[front]);
            if (i < j) swap(a[i], a[j]);
        } while (i < j);
        swap(a[front], a[j]);

        quicksortWorst(a, front, j - 1, depth+1); // 對左邊的數進行排序
        quicksortWorst(a, j + 1, end, depth+1);   // 對右邊的數進行排序
    }
}

// quick sort
template<class T>
void quicksortNormal(vector<T>& a, const int& front, const int& end, int depth) {
    if (front < end) {
        // 更新最大記憶體使用量
        update_max_memory(depth * 4 * sizeof(int));

        // 取三個數的最大值
        int mid = (front + end) / 2;
        if (a[mid] < a[front]) swap(a[front], a[mid]);
        if (a[end] < a[front]) swap(a[front], a[end]);
        if (a[mid] < a[end]) swap(a[mid], a[end]);

        // 將pivot移到最左邊
        swap(a[front], a[end]);

        // 將比pivot小的數移到左邊，比pivot大的數移到右邊
        int i = front, j = end + 1;
        do {
            do i++; while (a[i] < a[front]);
            do j--; while (a[j] > a[front]);
            if (i < j) swap(a[i], a[j]);
        } while (i < j);
        swap(a[front], a[j]);

        quicksortNormal(a, front, j - 1, depth+1); // 對左邊的數進行排序
        quicksortNormal(a, j + 1, end, depth+1);   // 對右邊的數進行排序
    }
}
template<class T>
vector<T> quicksort(vector<T> a, const int& front, const int& end, const bool& worst) {
    if(worst)
        quicksortWorst(a, front, end, 1);
    else
        quicksortNormal(a, front, end, 1);
    return a;
}

// heap sort
template<class T>
void maxheapify(vector<T>& a, const int& root, const int& len) {
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    int largest = root;

    // 更新最大記憶體使用量
    update_max_memory(3 * sizeof(int)); 

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
    result.reserve(left.size() + right.size());
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

    // 更新記憶體使用量
    size_t current_memory = memory_of_vector(left) + memory_of_vector(right);
    if (current_memory > max_memory_usage) {
        max_memory_usage = current_memory;
    }

    return result;
}

template<class T>
vector<T> mergesort(vector<T> a, const int& front, const int& end) {
    // 只剩一個元素時，回傳單一元素的vector
    if (front >= end) {
        vector<T> single = { a[front] };
        return single;
    }

    int mid = (front + end) / 2;
    vector<T> left = mergesort(a, front, mid);
    vector<T> right = mergesort(a, mid + 1, end);

    size_t current_memory = memory_of_vector(left) + memory_of_vector(right);
    update_max_memory(current_memory);
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
    if(depth >= log2(a.size())){
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
    int data[] = {500, 1000, 2000, 3000, 4000, 5000};
    int n;
    double initMemory;
    vector<int> a;
    vector<double> memoryData;
    
    ofstream file("memory_usage.csv");
    file << "n,InsertsortMemoryUsage,QuicksortMemoryUsage,MeragesortMemoryUsage,HeapsortMemoryUsage \n"; // 標題行

    for(int i = 0; i < sizeof(data)/sizeof(int); i++){
        n = data[i];
        cout << "n = " << n << endl;
        file << n << ",";
        generate_random_data(n);
        a = read_data("data.txt", n);
        
        max_memory_usage = 0;
        insertsort(a, n);
        cout << "Insertsort memory usage: " << max_memory_usage << " B" << endl;
        file << max_memory_usage << ",";

        max_memory_usage = 0;
        quicksort(a, 0, n - 1, false);
        cout << "Quicksort memory usage: " << max_memory_usage << " B" << endl;
        file << max_memory_usage << ",";

        max_memory_usage = 0;
        mergesort(a, 0, n - 1);
        cout << "Mergesort memory usage: " << max_memory_usage << " B" << endl;  
        file << max_memory_usage << ",";

        max_memory_usage = 0;
        heapsort(a);
        cout << "Heapsort memory usage: " << max_memory_usage << " B" << endl;
        file << max_memory_usage << "," << endl;
    }
    file.close();
}
