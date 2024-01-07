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
int N[] = {16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072};
int NSize = 14;
double runTimes[14];

double sortUp(int m, int n, vector<int> &arr);
void sortDown(int m, int n, vector<int> &arr);

void mergeUp(int m, int n, vector<int> &arr) {
    if (n == 0) {
        return;
    }
    for (int i = 0; i < n; i++) {
        if (arr[m+i] > arr[m+i+n]) {
            int temp = arr[m+i];
            arr[m+i] = arr[m+i+n];
            arr[m+i+n] = temp;
        }
    }
    mergeUp(m, n/2, arr);
    mergeUp(m+n, n/2, arr);
}

void mergeDown(int m, int n, vector<int> &arr) {
    if (n == 0) {
        return;
    }
    for (int i = 0; i < n; i++) {
        if (arr[m+i] < arr[m+i+n]) {
            int temp = arr[m+i];
            arr[m+i] = arr[m+i+n];
            arr[m+i+n] = temp;
        }
    }
    mergeDown(m, n/2, arr);
    mergeDown(m+n, n/2, arr);
}

void populateArray(int size, vector<int> &arr) {
    arr.resize(0);
    for (int i = 0; i < size; i++) {
        int test = rand();
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
        runTimes[i] = sortUp(0, N[i], arr);
        cout << "The time to complete " << N[i] << " elements is " << runTimes[i] << endl;
        // cout << "array after sort"  << endl;
        // printArr(arr);
    }
    ofstream file;
    file.open("bitonicSortValues");
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

double sortUp(int m, int n, vector<int> &arr) {
    chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();
    
    if (n == 1) {
        return -1;
    }
    sortUp(m, n/2, arr);
    sortDown(m+(n/2), n/2, arr);
    mergeUp(m, n/2, arr);

    chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> timer = endTime - beginTime;
    return timer.count();
}

void sortDown(int m, int n, vector<int> &arr) {
    if (n == 1) {
        return;
    }
    sortUp(m, n/2, arr);
    sortDown(m+(n/2), n/2, arr);
    mergeDown(m, n/2, arr);
}