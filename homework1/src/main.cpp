#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <algorithm>
using namespace std;

vector<int> read_data(const string& filename, int& n) {
    ifstream in;
    in.open(filename);
    if (!in.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    // Ū�J��Ƶ���
    in >> n;
    vector<int> a(n);

    // Ū�J���
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
        cerr << "�L�k�}���ɮ�: " << "data.txt" << endl;
        return;
    }

    srand(time(NULL)); // �]�w�H���ؤl

    out << n << endl; // �g�J��Ƶ���
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
template<class T>
vector<T> insertsort(vector<T> a, const int& left, const int& right) {
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
    return a;
}

// quick sort
template<class T>
void quicksortWorst(vector<T>& a, const int& front, const int& end) {
    if (front < end) {
        int mid = a[(front + end) / 2], pivot;
        // ���T�Ӽƪ��̤j��
        pivot = front;
        if (mid >= a[front] && mid >= a[end])
            pivot = (front + end) / 2;
        if ((a[end] >= a[front] && a[end] >= mid))
            pivot = end;

        // �Npivot����̥���
        swap(a[front], a[pivot]);

        // �N��pivot�p���Ʋ��쥪��A��pivot�j���Ʋ���k��
        int i = front, j = end + 1;
        do {
            do i++; while (a[i] < a[front]);
            do j--; while (a[j] > a[front]);
            if (i < j) swap(a[i], a[j]);
        } while (i < j);
        swap(a[front], a[j]);

        quicksortWorst(a, front, j - 1); // �索�䪺�ƶi��Ƨ�
        quicksortWorst(a, j + 1, end);   // ��k�䪺�ƶi��Ƨ�
    }
}

// quick sort
template<class T>
void quicksortNormal(vector<T>& a, const int& front, const int& end) {
    if (front < end) {
        int mid = (front + end) / 2;
        if (a[mid] < a[front]) swap(a[front], a[mid]);
        if (a[end] < a[front]) swap(a[front], a[end]);
        if (a[mid] < a[end]) swap(a[mid], a[end]);
        swap(a[front], a[end]);

        // �N��pivot�p���Ʋ��쥪��A��pivot�j���Ʋ���k��
        int i = front, j = end + 1;
        do {
            do i++; while (a[i] < a[front]);
            do j--; while (a[j] > a[front]);
            if (i < j) swap(a[i], a[j]);
        } while (i < j);
        swap(a[front], a[j]);

        quicksortNormal(a, front, j - 1); // �索�䪺�ƶi��Ƨ�
        quicksortNormal(a, j + 1, end);   // ��k�䪺�ƶi��Ƨ�
    }
}
template<class T>
vector<T> quicksort(vector<T> a, const int& front, const int& end, const bool& worst) {
    if (worst)
        quicksortWorst(a, front, end);
    else
        quicksortNormal(a, front, end);
    return a;
}

// heap sort
template<class T>
void maxheapify(vector<T>& a, int root, int left, int right) {
    int l = 2 * (root - left) + 1 + left; 
    int r = 2 * (root - left) + 2 + left; 
    int largest = root;

    // 檢查左子節點是否在範圍內且大於當前最大值
    if (l <= right && a[l] > a[largest]) {
        largest = l;
    }

    // 檢查右子節點是否在範圍內且大於當前最大值
    if (r <= right && a[r] > a[largest]) {
        largest = r;
    }

    // 如果最大值不是根節點，則交換並遞迴調整
    if (largest != root) {
        swap(a[root], a[largest]);
        maxheapify(a, largest, left, right);
    }
}

// 建立最大堆積
template<class T>
void maxheap(vector<T>& a, int left, int right) {
    // 從最後一個非葉節點開始，逐一調整
    for (int i = (right - left) / 2 + left; i >= left; i--) {
        maxheapify(a, i, left, right);
    }
}

// Heap Sort 主函數
template<class T>
vector<T> heapsort(vector<T> a, int left, int right) {
    if (left >= right || left < 0 || right >= a.size()) {
        return a; // 無效範圍，直接返回
    }

    maxheap(a, left, right); // 建立最大堆積
    for (int i = right; i > left; i--) {
        swap(a[left], a[i]); // 將最大元素放到範圍末端
        maxheapify(a, left, left, i - 1); // 調整剩餘部分
    }
    return a;
}

// merge sort
// �N���k�}�C�X�֨ñƦC
template<class T>
vector<T> merge(const vector<T>& left, const vector<T>& right) {
    vector<T> result;
    int i, j;
    i = j = 0;

    // �Y���}�C�M�k��ɳ��٨S�쩳�A�~����
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

    // �N�ѤU���ƭȶ�J���G
    while (i < left.size())
        result.push_back(left[i++]);
    while (j < right.size())
        result.push_back(right[j++]);

    return result;
}

template<class T>
vector<T> mergesort(const vector<T>& a, const int& front, const int& end) {
    // �u�Ѥ@�Ӥ����ɡA�^�ǳ�@������vector
    if (front == end)
    {
        vector<T> result;
        result.push_back(a[front]);
        return result;
    }

    int mid = (front + end) / 2;

    vector<T> left = mergesort(a, front, mid),
        right = mergesort(a, mid + 1, end);

    // �X�֨ñƦC
    return merge(left, right);
}

// �ˬd�ƧǬO�_���T
template<class T>
bool checksort(const vector<T>& a, int n) {
    for (int i = 0; i < n - 1; i++)
        if (a[i] > a[i + 1]) return false;
    return true;
}

template<class T>
void compositesort(vector<T>& a, const int& left, const int& right, int depth) {
    int size = right - left + 1;

    if (left >= right) return;

    // �p�ƾڨϥ�insertSort
    if (size <= 30) {
        a = insertsort(a, left, right);
        return;
    }

    // ���j�`�׹L�`��heapSort
    if (depth >= log2(a.size())) {
        a = heapsort(a, left, right);
        return;
    }

    // �w�]�ϥ�quickSort
    // ���T�Ӽƪ�������
    int mid = (left + right) / 2;
    if (a[mid] < a[left]) swap(a[left], a[mid]);
    if (a[right] < a[left]) swap(a[left], a[right]);
    if (a[mid] < a[right]) swap(a[mid], a[right]);
    swap(a[left], a[right]);

    int i = left, j = right + 1;
    do {
        do i++; while (a[i] < a[left]);
        do j--; while (a[j] > a[left]);
        if (i < j) swap(a[i], a[j]);
    } while (i < j);

    swap(a[left], a[j]);

    compositesort(a, left, j - 1, depth+1);
    compositesort(a, j + 1, right, depth+1);
}

int main() {

    // ���V���p
    int data = 30000;
    int n;
    vector<int> result;
    double start, stop;
    vector<int> a = read_data("data.txt", n);


    // ���մ��J�Ƨ�
    // generate_insertion_worst(data);
    // a = read_data("data.txt", n);
    //double time = 0, count = 0;
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

    // ���էֳt�Ƨ�
    // cout << n << endl;
    // memoryUsage();
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

    // // ���վ�X�Ƨ�
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

    // // ���հ�n�Ƨ�
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


    // �������p      
    // generate_random_data(data);

    double time2 = 0, count2 = 0;
    double time3 = 0, count3 = 0;
    double time4 = 0, count4 = 0;
    double time5 = 0,count5= 0;
    double time6 = 0, count6 = 0;
    double time7 = 0, count7 = 0;

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
        result = heapsort(a, 0, n - 1);
        stop = clock();
        if (checksort(result, n)) {
            time5 += (stop - start) / CLOCKS_PER_SEC;
            count5++;
        }
        vector<int> a2 = a;
        start = clock();
        compositesort(a2,0,n-1,1);
        stop = clock();
        if (checksort(a2, n)) {
            time6 += (stop - start) / CLOCKS_PER_SEC;
            count6++;
        }
        start = clock();
        sort(a.begin(),a.end());
        stop = clock();
        if (checksort(a, n)) {
            time7 += (stop - start) / CLOCKS_PER_SEC;
            count7++;
        }
    }
     
    std::cout << "insertsort time:" << time2 / count2 << "s" << endl;
    std::cout << "quicksort time:" << time3 / count3 << "s" << endl;
    std::cout << "mergesort time:" << time4 / count4 << "s" << endl;
    std::cout << "heapsort time:" << time5 / count5 << "s" << endl;
    std::cout << "compositesort time:" << time6 / count6 << "s" << endl;
    std::cout << "sort time:" << time7 / count7 << "s" << endl;
}
