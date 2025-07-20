#include <iostream>
#include <stack>
using namespace std;

int P1(int m, int n) {
    stack<int> stk;

    stk.push(m);
    while (!stk.empty()) {
        m = stk.top();
        stk.pop();

        if (m == 0) {
            n = n + 1;
        } else if (n == 0) {
            stk.push(m - 1);
            n = 1;
        } else {
            stk.push(m - 1);
            stk.push(m);
            n = n - 1;
        }
    }

    return n;
}

int main() {
    int m = 3, n = 2;
    int result = P1(m, n);
    cout << "P2(" << m << "," << n << ") = " << result << endl;

    return 0;
}