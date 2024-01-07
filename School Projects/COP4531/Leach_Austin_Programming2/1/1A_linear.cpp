#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int size = 1000000;

int linearProbing(int number, vector<int> &hashtable, int iteration) {
    int i = (number + iteration) % size;
    if (hashtable[i] == -1) {
        hashtable[i] = number;
        return iteration+1;
    } 
    else {
        iteration++;
        linearProbing(number, hashtable, iteration);
    }
}

int main() {
    srand(time(NULL));

    vector<int> hashtable;
    vector<int> probes;
    hashtable.resize(size);
    probes.resize(0);
    for (int i = 0; i < size; i++) {
        hashtable[i] = -1;  // can never be a negative value
    }
    
    // can get to load factor .99
    for (int i = 0; i < size - size/100; i++) {
        int random = rand();    //rand will never produce a negative number
        int probeValue = linearProbing(random, hashtable, 0);
        if (i > size/2 && (i % 100) == 0) {
            probes.push_back(probeValue);
        }
    }

    ofstream file;
    file.open("linearProbes");
    for (int i = 0; i < probes.size(); i++) {
        file << probes[i] << endl;
    }
    file.close();
    // prints the array, 100000 takes a long time so it is commented out
    // for (int i = 0; i < size; i++) {
    //     cout << hashtable[i] << endl;
    // }

    return 0;
}