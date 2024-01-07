// Austin Leach
// uses C++11 on linprog
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include <vector>
#include <chrono>
#include <time.h>

using namespace std;

// sizes of arrays 
int N[] = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};
int NSize = 11;
double runTimes[11];

void heapify(vector<int> &arr, int i, int heapsize) {
    int left = i * 2;
    int right = i * 2 + 1;
    int temp;

    if (left <= heapsize && arr[left] > arr[i]) {
        temp = left;
    } else {
        temp = i;
    }

    if (right <= heapsize && arr[right] > arr[temp]) {
        temp = right;
    }

    if (temp != i) {
        int swap = arr[i];
        arr[i] = arr[temp];
        arr[temp] = swap;
        heapify(arr, temp, heapsize);
    }
}

void buildHeap(vector<int> &arr) {
    int heapsize = arr.size() - 1;
    for (int i = heapsize/2; i > 0; i--) {
        heapify(arr, i, heapsize);
    }
}

double heapSort(vector<int> &arr) {
    chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();
    
    buildHeap(arr);

    int heapsize = arr.size()-1;
    for (int i = heapsize; i > 1; i--) {
        int swap = arr[1];
        arr[1] = arr[i];
        arr[i] = swap;
        heapsize--;
        heapify(arr, 1, heapsize);
    }
    
    chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> timer = endTime - beginTime;
    return timer.count();
}

void populateArray(int size, vector<int> &arr) {
    arr.resize(0);
    for (int i = 1; i <= size; i++) {
        int test = rand() % 65536;
        arr.push_back(test);
    }
}

void printArr (vector<int> &arr) {
    for (int j = 1; j < arr.size(); j++) {
        cout << arr[j] << endl;
    }
}

int main() {
    vector<int> arr;
    srand(time(NULL));
    for (int i = 0; i < NSize; i++) {
        populateArray(N[i], arr);
        //printArr(arr);
        runTimes[i] = heapSort(arr);
        cout << "The time to complete " << N[i] << " elements is " << runTimes[i] << endl;
        //cout << "array after sort" << endl;
        //printArr(arr);
    }
    ofstream file;
    file.open("heapSortValues");
    for (int i = 0; i < NSize; i++) {
        if (i == NSize-1) {
            file << runTimes[i];
        } else {
            file << runTimes[i] << ",";
        }
    }
    file.close();
    return 0;
}