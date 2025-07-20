#include <iostream>
using namespace std;

int P1(int m, int n) {
    if (m == 0) return n + 1;
    if (n == 0) return P1(m - 1, 1);
    return P1(m - 1, P1(m, n - 1));
}

int main() {
    int m=2, n=2;
  
    int result = P1(m, n);
    cout << "P1(" << m << "," << n << ") = " << result << endl;

    return 0;
}
