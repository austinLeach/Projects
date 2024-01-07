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
// Computer can not handle anything above 100000 in a reasonable time 
int N[] = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};
int NSize = 11;
double runTimes[11];


void merge(vector<int> &arr, int begin, int middle, int end) {
    int n1 = middle - begin + 1;
    int n2 = end - middle;
    int left[n1];
    int right[n2]; 

    for (int i = 0; i < n1; i++) {
        left[i] = arr[begin+i];
    }
    for (int i = 0; i < n2; i++) {
        right[i] = arr[middle+i+1];
    }

    int i = 0, j = 0, k = begin;
    for (; i < n1 && j < n2; k++) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
    }
 
    for (; i < n1; i++, k++) {
        arr[k] = left[i];
    }
    for (; j < n2; j++, k++) {
        arr[k] = right[j];
    }
}

double mergeSort(vector<int> &arr, int begin, int end) {
    chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();
    
    if (begin < end) {
        int middle = ((begin + end) / 2);
        mergeSort(arr, begin, middle);
        mergeSort(arr, middle+1, end);
        merge(arr, begin, middle, end);
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
        runTimes[i] = mergeSort(arr, 0, arr.size()-1);
        cout << "The time to complete " << N[i] << " elements is " << runTimes[i] << endl;
        // cout << "array after sort" << endl;
        // printArr(arr);
    }
    ofstream file;
    file.open("mergeSortValues");
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