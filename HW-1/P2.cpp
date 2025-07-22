#include <iostream>
using namespace std;

void powerset(char S[], int n, char subset[], int index, int subsetSize) {
    if (index == n) {
        cout << "{";
        for (int i = 0; i < subsetSize; i++) {
            cout << subset[i];
            if (i < subsetSize - 1) cout << ",";
        }
        cout << "}";
        return;
    }

    powerset(S, n, subset, index + 1, subsetSize);
    cout << ", ";

    subset[subsetSize] = S[index];
    powerset(S, n, subset, index + 1, subsetSize + 1);
}

void printPowerset(char S[], int n) {
    char subset[n];
    cout << "{";
    powerset(S, n, subset, 0, 0);
    cout << "}" << endl;
}

int main() {
    char S[] = {'a', 'b', 'c'};
    int n = 3;
    cout << "powerset(S) = ";
    printPowerset(S, n);
    
    return 0;
}