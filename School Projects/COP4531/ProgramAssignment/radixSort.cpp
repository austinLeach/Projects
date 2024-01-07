// Austin Leach
// uses C++11 on linprog
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include <cmath>
#include <vector>
#include <chrono>
#include <time.h>

using namespace std;

// sizes of arrays
int N[] = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};
int NSize = 11;
double runTimes[11];

void printArr (vector<int> &arr) {
    for (int j = 0; j < arr.size(); j++) {
        cout << arr[j] << endl;
    }
}

void countingSort(vector<int> &arr, int digit) {
    vector<int> outputArr;
    outputArr.resize(arr.size());
    int tempArr [10];   //one for each digit
    
    for (int i = 0; i < 10; i++) {
        tempArr[i] = 0;
    }
    for (int i = 0; i < arr.size(); i++) {
        tempArr[(arr[i] / digit) % 10]++;
    }
    for (int i = 1; i < 10; i++) {
        tempArr[i] += tempArr[i-1];
    }
    for (int i = arr.size()-1; i >= 0; i--) {
        outputArr[tempArr[(arr[i] / digit) % 10] - 1] = arr[i];
        tempArr[(arr[i] / digit) % 10]--;
    }
    arr.assign(outputArr.begin(), outputArr.end());
}

double radixSort(vector<int> &arr, int digit) {
    chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();

    for (int i = 0; i < digit; i++) {
        countingSort(arr, pow(10, i));
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

int main() {
    vector<int> arr;
    const int maxDigit = 5;
    srand(time(NULL));
    for (int i = 0; i < NSize; i++) {
        populateArray(N[i], arr);
        //printArr(arr);
        runTimes[i] = radixSort(arr, maxDigit);
        cout << "The time to complete " << N[i] << " elements is " << runTimes[i] << endl;
        // cout << "array after sort"  << endl;
        // printArr(arr);
    }
    ofstream file;
    file.open("radixSortValues");
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