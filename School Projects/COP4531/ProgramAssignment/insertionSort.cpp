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
// Computer can not handle anything above 50000 in a reasonable time 
int N[] = {10, 50, 100, 500, 1000, 5000, 10000, 50000, /*100000, 500000, 1000000*/};
int NSize = 8;
double runTimes[11];

double insertionSort(vector<int> &arr) {
    chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();

    for (int i = 2; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j > 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
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
        runTimes[i] = insertionSort(arr);
        cout << "The time to complete " << N[i] << " elements is " << runTimes[i] << endl;
        // cout << "array after sort" << endl;
        //printArr(arr);
    }
    ofstream file;
    file.open("insertionSortValues");
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