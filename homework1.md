# 41141151

作業一

## 解題說明

### Problem 1
本題要求實作一個Ackermann 函數，並以兩種方式進行實現：
1. 遞迴版本
2. 非遞迴版本

### Problem 2
本題要求實作一個函式，能夠列出給定集合的所有子集合，並以遞迴方式完成。
1. 用包含或不包含來找出一個集合中的所有子集合

2. 用遞迴的方式來構建所有可能的組合




## 解題策略

### Problem 1

1. 當 $m = 0$ 時，根據定義，直接回傳 $n + 1$，此為遞迴的終止條件之一。

2. 當 $m > 0$ 且 $n = 0$ 時，呼叫並回傳 $A(m - 1, 1)$。

3. 當 $m > 0$ 且 $n > 0$ 時，進行巢狀遞迴呼叫，回傳 $A(m - 1, A(m, n - 1))$。

4. 當一般的遞迴實作在 $m$ 與 $n$ 較大時會造成堆疊溢位時，以 **手動堆疊 stack** 方式模擬遞迴過程，避免系統堆疊過深。

### Problem 2

1. 集合中的每個元素有兩種選擇：包含或不包含在子集合中。

2. 當處理完所有元素時，輸出目前子集合。

3. 每次遞迴根據是否選擇當前元素，動態調整子集合內容與大小。



## 程式實作

### Problem 1
### 遞迴

```cpp
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
```
### 非遞迴
```cpp
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

```

### Problem 2

```cpp
#include <iostream>
using namespace std;

void powerset(char S[], int n, char subset[], int index, int subsetSize, bool &first) {
    if (index == n) {
        if (!first) cout << ", ";
        cout << "{";
        for (int i = 0; i < subsetSize; i++) {
            cout << subset[i];
            if (i < subsetSize - 1) cout << ",";
        }
        cout << "}";
        first = false;
        return;
    }

    powerset(S, n, subset, index + 1, subsetSize, first);

    subset[subsetSize] = S[index];
    powerset(S, n, subset, index + 1, subsetSize + 1, first);
}

void printPowerset(char S[], int n) {
    char subset[n];
    bool first = true;
    cout << "{";
    powerset(S, n, subset, 0, 0, first);
    cout << "}" << endl;
}

int main() {
    char S[] = {'a', 'b', 'c'};
    int n = 3;
    cout << "powerset(S) = ";
    printPowerset(S, n);

    return 0;
}

```

---

## 效能分析

### Problem 1

1. 時間複雜度：程式的時間複雜度為 O(A(m, n))

2. 空間複雜度：空間複雜度為 O(A(m, n))




### Problem 2

1. 時間複雜度：O(2^n)

2. 空間複雜度：O(n)

---

## 測試與驗證

### 測試案例

### Problem 1

| 測試案例 | 參數 $(m, n)$ | 預期輸出 | 實際輸出 |
|----------|----------------|-----------|-----------|
| 測試一   | (0, 1)         | 2         | 2         |
| 測試二   | (1, 2)         | 4         | 4         |
| 測試三   | (2, 2)         | 7         | 7         |
| 測試四   | (3, 2)         | 29        | 29        |
| 測試五   | (3, 3)         | 61        | 61        |



### 編譯與執行指令

```bash
g++ -std=c++17 -o ackermann ackermann.cpp
./ackermann
```

### 結論

1. 程式能正確計算 Ackermann 函數，符合測試案例的預期以及實際輸出。

2. 遞迴版本與非遞迴版本都能正確輸出結果，且非遞迴版本可以避免系統堆疊溢位。

3. 測試案例有多種不同輸入組合，確保程式計算正確。

4. 由於 Ackermann 函數的計算量非常大，輸入數值過高時會導致程式運算時間和記憶體需求迅速增加，需要注意不能輸入太大的數值。
---

### Probelm 2
| 測試案例 | 輸入集合        | 預期輸出及實際輸出 
|----------|-------------------|------------------------|
| 測試一   | { }                | { }
| 測試二   | {a}               | { }, {a}
| 測試三   | {a, b}            | { }, {a}, {b}, {a,b}
| 測試四   | {a, b, c}         |{ }, {c}, {b}, {b,c}, {a}, {a,c}, {a,b}, {a,b,c}


### 編譯與執行指令
```bash
g++ -std=c++17 -o powerset powerset.cpp
./powerset
```

### 結論

1. 程式能夠列出所有子集合，包含空集合。

2. 程式能正確給出空集合及不同大小的集合並且實際輸出符合預期輸出。

4. 子集合需要注意數量，太大會導致執行時間增加很多。


## 申論及開發報告

### Problem 1
### 選擇遞迴的原因
在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. **邏輯清晰，符合數學定義**  
   Ackermann 函數的數學定義本身就是遞迴形式：


$$
A(m,n) = \begin{cases}
n + 1 & \text{if } m = 0 \\
A(m-1, 1) & \text{if } n = 0 \\
A(m-1, A(m, n-1)) & \text{otherwise}
\end{cases}
$$

   使用遞迴函式能直觀地反映這個結構，使程式碼簡潔且易於閱讀。

2. **程式碼較短且易於維護**  
   遞迴版本程式碼簡潔，較不需額外變數或狀態管理，方便除錯和理解。




### 選擇非遞迴的原因

1. 遞迴呼叫會消耗大量堆疊空間，當輸入變大時容易造成系統溢出。

2. 利用 stack 來手動模擬遞迴過程，避免系統堆疊限制。

3. 非遞迴版本在理論複雜度相同的前提下，更穩定且能支援更深的運算。

Ackermann 函數本身是遞迴定義，使用遞迴實作能讓程式邏輯清楚且簡潔，易於理解和維護。
不過遞迴呼叫可能造成堆疊溢位，因此我們也實作非遞迴版本，利用 stack 模擬遞迴，避免系統限制，提高穩定性。
兩者在效能上相當，但非遞迴版本更適合處理較大輸入，兩種方法可以進行互補。
-*

---

### Problem 2

本題目要求實作一個能找出所有子集合的演算法。  

透過遞迴方式進行「包含」與「不包含」某元素的決策，找出所有可能的子集合組合。

以輸入 `S = {a, b, c}` 為例，程式輸出如下：

$$
\text{powerset}(S) =
\{ \{\}, \{c\}, \{b\}, \{b,c\}, \{a\}, \{a,c\}, \{a,b\}, \{a,b,c\} \}
$$

程式結構簡潔，邏輯清楚，適合用於集合規模不大的情況。
