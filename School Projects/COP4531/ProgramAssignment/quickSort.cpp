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

int partition(vector<int> &arr, int begin, int end) {
    int pivot = arr[end];
    int i = begin-1;
    for (int j = begin; j < end; j++) {
        if (arr[j] <= pivot) {
            i++;
            int swap = arr[i];
            arr[i] = arr[j];
            arr[j] = swap;
        }
    }
    int swap = arr[i+1];
    arr[i+1] = arr[end];
    arr[end] = swap;
    return i+1;
}

double quickSort(vector<int> &arr, int begin, int end) {
    chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();
    
    if (begin < end) {
        int pivot = partition(arr, begin, end);
        quickSort(arr, begin, pivot-1);
        quickSort(arr, pivot+1, end);
    }

    chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> timer = endTime - beginTime;
    return timer.count();
}

void populateArray(int size, vector<int> &arr) {
    arr.resize(0);
    for (int i = 0; i < size; i++) {
        int test = rand() % 65536;
        arr.push_back(test);
    }
}

void printArr (vector<int> &arr) {
    for (int j = 0; j < arr.size(); j++) {
        cout << arr[j] << endl;
    }
}

int main() {
    vector<int> arr;
    srand(time(NULL));
    for (int i = 0; i < NSize; i++) {
        populateArray(N[i], arr);
        //printArr(arr);
        runTimes[i] = quickSort(arr, 0, arr.size()-1);
        cout << "The time to complete " << N[i] << " elements is " << runTimes[i] << endl;
        // cout << "array after sort" << endl;
        // printArr(arr);
    }
    ofstream file;
    file.open("quickSortValues");
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