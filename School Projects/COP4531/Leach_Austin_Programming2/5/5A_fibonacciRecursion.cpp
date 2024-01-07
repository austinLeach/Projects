#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

using namespace std;

int fibonacci(int ithNumber) {
    if (ithNumber == 1) {
        return 1;
    }
    else if (ithNumber == 0) {
        return 0;
    }

    return (fibonacci(ithNumber-1) + fibonacci(ithNumber-2));
}

int main() {
    vector<double> times; // used to keep track of runtimes

    // 100000 can not be ran in a reasonable time
    for (int i = 10; i <= 40; i+=5) {
        chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();

        int result = fibonacci(i);

        chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> timer = endTime - beginTime;
        times.push_back(timer.count());
        
        cout << result << endl;
    }

    ofstream file;
    file.open("fibonacciRecursionValues");
    for (int i = 0; i < times.size(); i++) {
        file << times[i] << endl;
    }
    file.close();
    
    return 0;
}