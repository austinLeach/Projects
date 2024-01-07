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
int N[] = {10, 50, 100, 500, 1000, 5000, 10000};
int NSize = 7;
double runTimes[7];

double bubbleSort(vector<int> &arr) {
    chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();
    
    int limit = arr.size();
    int i = -1;
    while (i < limit) {
        bool flag = false;
        i++;
        limit--;
        for (int j = i; j < limit; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                flag = true;
            }
        }
        if (!flag) {
            break;
        }

        flag = false;
        for (int j = limit - 1; j >= i; j--) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                flag = true;
            }
        }
        if (!flag) {
            break;
        }

    }

    chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> timer = endTime - beginTime;
    return timer.count();
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
        runTimes[i] = bubbleSort(arr);
        cout << "The time to complete " << N[i] << " elements is " << runTimes[i] << endl;
        // cout << "array after sort"  << endl;
        // printArr(arr);
    }
    ofstream file;
    file.open("biDirectionalBubbleSortValues");
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