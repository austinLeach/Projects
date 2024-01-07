#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

using namespace std;

long double fibonacci(int ithNumber, vector<long double> &memoizedArr) {
    long double firstFibonacci;
    long double secondFibonacci;

    if (ithNumber == 1) {
        memoizedArr[ithNumber] = 1;
        return 1;
    }
    else if (ithNumber == 0) {
        memoizedArr[ithNumber] = 0;
        return 0;
    }

    if (memoizedArr[ithNumber - 1]) {
        firstFibonacci = memoizedArr[ithNumber - 1];
    } else {
        firstFibonacci = fibonacci(ithNumber - 1, memoizedArr);
        memoizedArr[ithNumber - 1] = firstFibonacci;
    }

    if (memoizedArr[ithNumber - 2]) {
        secondFibonacci = memoizedArr[ithNumber - 2];
    } else {
        secondFibonacci = fibonacci(ithNumber - 2, memoizedArr);
        memoizedArr[ithNumber - 2] = secondFibonacci;
    }
    

    long double result = firstFibonacci + secondFibonacci;

    return result;
}

int main() {
    vector<double> times; // used to keep track of runtimes

     // long double is not large enough for 100000th fibonacci 
    vector<long double> memoizedArr;
    memoizedArr.resize(100000);
    for (int i = 100; i <= 10000; i+=100) {
        chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();

        long double result = fibonacci(i, memoizedArr);

        // clear array so that it does not have values from previous run
        memoizedArr.resize(0);

        chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> timer = endTime - beginTime;
        times.push_back(timer.count());

        cout << result << endl;
    }

    ofstream file;
    file.open("fibonacciMemoizeValues");
    for (int i = 0; i < times.size(); i++) {
        file << times[i] << endl;
    }
    file.close();
    
    return 0;
}