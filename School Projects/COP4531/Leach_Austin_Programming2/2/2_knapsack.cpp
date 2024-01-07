#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int knapsack (int n, int W, int iTable[], int wTable[]) {
    vector<vector<int>> c;

    c.resize(n);
    for (int i = 0; i < n; i++) {
        c[i].resize(W);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < W; j++) {
            c[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < W; j++) {
            if (i == 0 || j == 0) {
                c[i][j] = 0;
            }
            else if (wTable[i] > j) {
                c[i][j] = c[i-1][j];
            }
            else {
                c[i][j] = max(iTable[i] + c[i-1][j - wTable[i]], c[i-1][j]);
            }
        }
    }
    return c[n-1][W-1];
}

int main() {
    int W = 335732;
    int n = 100;
    int iTable[n];

    for (int i = 1; i <= n; i++) {
        iTable[i] = 1;
    }

    int wTable[n];

    for (int i = 1; i <= n; i++) {
        int temp = 1000 * pow(i, .5);
        wTable[i-1] = temp;
    }
    
    int value = knapsack(n, W, iTable, wTable);   
    cout << value << endl;

    return 0;
}