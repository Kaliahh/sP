#include <iostream>
#include <vector>
#include <utility>
#include <chrono>
#include <cstring>
using namespace std;

void swap_ends(int*, int);
void swap_ends(vector<int>&);
void swap_ends_static(int*, int);
void swap_ends_dynamic(int*, int);

void inputOutput() {
    char a[50];

    std::cout << "Write some input: ";
    std::cin >> a;
    std::cout << "This is your input: " << a << std::endl;
    std::cerr << "This is your input as an error: " << a << std::endl;
    std::clog << "This is your input as a log?: " << a << std::endl;
}

void swap_ends(int arr[], int size) {
    for (int i = size/2 - 1, j = size - 1; i >= 0; --i, --j)
        swap(arr[i], arr[j]);
}

void swap_ends(vector<int>& arr) { // overloading the same fn-name
    for (int i = arr.size()/2 - 1, j = arr.size() - 1; i >= 0; --i, --j)
        swap(arr[i], arr[j]);
}

void printArray(const vector<int>& arr) {
    for (auto i : arr) {
        cout << i << " ";
    }
    cout << endl;
}

void printArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

void vectorAndArray() {
    int c_array[] = {1,2,3,4,5,6,7};
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7};
    vector<int>* vec_d = new vector<int>{1, 2, 3, 4, 5, 6, 7};

    for (auto i : c_array) {
        cout << i << " ";
    }
    cout << endl;

    printArray(c_array, sizeof(c_array)/sizeof(int));

    swap_ends(*vec_d);

    printArray(*vec_d);

    delete vec_d;
}


constexpr int arr_size = 10000000;



void swap_ends_static(int arr[], int size) {
    static int buffer[arr_size / 2];

    size_t copy = (sizeof(int) * size) / 2;

//    cout << size / 2 << endl;

    memcpy(buffer, arr, copy);

    memcpy(arr, arr + (size / 2), copy);

    memcpy(arr + (size / 2), buffer, copy);

//    for (int i = 0; i < size; i++) {
//        cout << arr[i] << ", ";
//    }
//    cout << endl;
}

void swap_ends_dynamic(int arr[], int size) {
    int* buffer = new int[arr_size / 2];

    size_t copy = (sizeof(int) * size) / 2;

    memcpy(buffer, arr, copy);

    memcpy(arr, arr + (size / 2), copy);

    memcpy(arr + (size / 2), buffer, copy);
}

int c_arr[arr_size];
vector<int> vec(arr_size);

void do_work() {
//    vector<int> vec(arr_size);

    int size = sizeof(c_arr) / sizeof(int);

//    swap_ends(c_arr, size);
//    swap_ends(vec);

    swap_ends_static(c_arr, size);
//    swap_ends_dynamic(c_arr, size);
}

void exercise1_2() {
    double sum = 0;
    double iterations = 100;

    for (int i = 0; i < iterations; i++) {
        auto t0 = chrono::high_resolution_clock::now();
        do_work();
        auto t1 = chrono::high_resolution_clock::now();

        sum += chrono::duration<double, milli>(t1-t0).count();
    }


    cout << sum / iterations << "ms" << endl;
}

int main() {

//    inputOutput();

//    vectorAndArray();

    exercise1_2();

    return 0;
}