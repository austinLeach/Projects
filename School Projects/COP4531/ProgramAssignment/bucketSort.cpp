// Austin Leach
// uses C++11 on linprog
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include <list>
#include <vector>
#include <chrono>
#include <time.h>

using namespace std;

// sizes of arrays
int N[] = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};
int NSize = 11;
double runTimes[11];

double bucketSort(vector<double> &arr) {
    chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();
    
    list<double> buckets[10]; // for 0.0 - 0.9
    for (int i = 0; i < arr.size(); i++) {
        int index = arr[i] * 10;
        buckets[index].push_back(arr[i]);
    }
    for (int i = 0; i < 10; i++) {
        buckets[i].sort();
    } 
    int j = 0;
    arr.resize(0);
    for (int i = 0; i < 10; i++) {
        while (!buckets[i].empty()) {
            arr.push_back(buckets[i].front());
            buckets[i].pop_front();
        }
    }

    chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> timer = endTime - beginTime;
    return timer.count();
}

void populateArray(int size, vector<double> &arr) {
    arr.resize(0);
    for (int i = 0; i < size; i++) {
        double test = double(rand()) / (double(RAND_MAX) + 1.0);
        arr.push_back(test);
    }
}

void printArr (vector<double> &arr) {
    for (int j = 0; j < arr.size(); j++) {
        cout << fixed <<arr[j] << endl;
    }
}

int main() {
    vector<double> arr;
    srand(time(NULL));
    for (int i = 0; i < NSize; i++) {
        populateArray(N[i], arr);
       // printArr(arr);
        runTimes[i] = bucketSort(arr);
        cout << "The time to complete " << N[i] << " elements is " << runTimes[i] << " ms" << endl;
        // cout << "array after sort" << endl;
        // printArr(arr);
    }

    ofstream file;
    file.open("bucketSortValues");
    for (int i = 0; i < 11; i++) {
        if (i == 10) {
            file << runTimes[i];
        } else {
            file << runTimes[i] << ",";
        }
    }
    file.close();
    return 0;
}