#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int size = 1000000;

// uses the iteration that it is on to determine what to subtract size by so it will have a different modulo each time
int myProbing(int number, vector<int> &hashtable, int iteration) {
    int i = (number + iteration*( number % (iteration+1))) % size;
   
    if (hashtable[i] == -1) {
        hashtable[i] = number;
        return iteration+1;
    } 
    else {
        iteration++;
        myProbing(number, hashtable, iteration);
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

    // can get to load factor .8
    for (int i = 0; i < size - size/5; i++) {
        int random = rand();    //rand will never produce a negative number
        int probeValue = myProbing(random, hashtable, 0);
        if (i > size/2 && (i % 100) == 0) {
            probes.push_back(probeValue);
        }
    }

    ofstream file;
    file.open("myProbes");
    for (int i = 0; i < probes.size(); i++) {
        file << probes[i] << endl;
    }
    file.close();
    // prints the array, 1000000 takes a long time so it is commented out
    // for (int i = 0; i < size; i++) {
    //     cout << hashtable[i] << endl;
    // }

    return 0;
}