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

double countingSort(vector<int> &arr, vector<int> &outputArr, int max) {
    chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();

    outputArr.resize(arr.size());
    
    int tempArr [max];
    for (int i = 0; i < max; i++) {
        tempArr[i] = 0;
    }
    for (int i = 0; i < arr.size()-1; i++) {
        tempArr[arr[i]]++;
    }
    for (int i = 0; i < max; i++) {
        tempArr[i] += tempArr[i-1];
    }
    for (int i = arr.size()-1; i >= 0; i--) {
        outputArr[tempArr[arr[i]]] = arr[i];
        tempArr[arr[i]]--;
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
    vector<int> outputArr;
    const int max = 65536;
    srand(time(NULL));
    for (int i = 0; i < NSize; i++) {
        populateArray(N[i], arr);
        //printArr(arr);
        runTimes[i] = countingSort(arr, outputArr, max);
        cout << "The time to complete " << N[i] << " elements is " << runTimes[i] << endl;
        // cout << "array after sort"  << endl;
        // printArr(outputArr);
    }
    ofstream file;
    file.open("countingSortValues");
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