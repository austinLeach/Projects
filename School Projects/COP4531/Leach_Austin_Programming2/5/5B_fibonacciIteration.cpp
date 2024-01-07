#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

using namespace std;

long double fibonacci(int ithNumber, vector<double> &times) {
    chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();

    long double fibonacci = 0;
    long double f0 = 0;
    long double f1 = 1;
    for (int i = 1; i < ithNumber; i++) {
        fibonacci = f0 + f1;
        f0 = f1;
        f1 = fibonacci;
    }

    chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> timer = endTime - beginTime;
    times.push_back(timer.count());
    return fibonacci;
}

int main() {
    vector<double> times; // used to keep track of runtimes

    // long double is not large enough for 100000th fibonacci 
    for (int i = 100; i <= 10000; i+=100) {
        long double result = fibonacci(i, times);
        cout << result << endl;
    }

    ofstream file;
    file.open("fibonacciIterationValues");
    for (int i = 0; i < times.size(); i++) {
        file << times[i] << endl;
    }
    file.close();

    return 0;
}