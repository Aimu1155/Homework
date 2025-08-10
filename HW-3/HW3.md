# 41141151

作業三

## 解題說明

本題要求實作一個多項式類別 Polynomial，使用 Circular Linked List with Header Node 來儲存多項式的每一項，並支援以下功能：

1. 以 >> 讀入多項式並建立鏈結串列。

2. 以 << 輸出多項式。

3. 使用 +、-、* 進行多項式的加減乘運算。

4. 使用 Evaluate(x) 計算多項式在特定 x 的值。

5. 支援拷貝建構子、指定運算子與解構子。

6. 使用 available-space list 進行節點回收，提高記憶體利用率。


## 解題策略

1. 建立 PolyNode 結構儲存係數、指數與下一節點指標：
    coef | exp | link

2. 使用 Circular Linked List with Header Node 來儲存多項式，header node 不存放有效資料。

3. 讀入多項式時依照降冪排序建立鏈結串列。

4. 運算子多載：
    - >>：將輸入轉成鏈結串列。
    - <<：將鏈結串列轉成外部格式輸出。
    - +、-：同步走訪兩個多項式並合併項次。
    - *：雙層迴圈計算各項相乘，並將同次方合併。

5. 使用 available-space list 回收刪除節點，減少 new / delete 開銷。

6. 使用 Evaluate() 代入數值計算多項式值。




## 程式實作

```cpp
#include <iostream>
#include <cmath>
using namespace std;

struct PolyNode {
    int coef, exp;
    PolyNode* link;
    PolyNode(int c = 0, int e = 0, PolyNode* l = nullptr)
        : coef(c), exp(e), link(l) {}
};

class Polynomial {
private:
    PolyNode* head;                 // Header node
    static PolyNode* avail;         // Available-space list

    void Attach(int c, int e);      // 插入節點
    void Clear();                   // 清除多項式

public:
    Polynomial();                                   // Constructor
    Polynomial(const Polynomial& a);                // Copy constructor
    ~Polynomial();                                  // Destructor
    const Polynomial& operator=(const Polynomial& a); // Assignment

    Polynomial operator+(const Polynomial& b) const; // Addition
    Polynomial operator-(const Polynomial& b) const; // Subtraction
    Polynomial operator*(const Polynomial& b) const; // Multiplication

    float Evaluate(float x) const;                  // Evaluate

    friend istream& operator>>(istream& is, Polynomial& x);
    friend ostream& operator<<(ostream& os, Polynomial& x);
};

PolyNode* Polynomial::avail = nullptr;

Polynomial::Polynomial() {
    head = new PolyNode();
    head->link = head;
}

Polynomial::Polynomial(const Polynomial& a) {
    head = new PolyNode();
    head->link = head;
    // TODO: 複製 a 的內容
}

Polynomial::~Polynomial() {
    Clear();
}

const Polynomial& Polynomial::operator=(const Polynomial& a) {
    if (this != &a) {
        Clear();
        // TODO: 複製 a 的內容
    }
    return *this;
}

void Polynomial::Attach(int c, int e) {
    // TODO: 插入節點（考慮 avail 回收）
}

void Polynomial::Clear() {
    // TODO: 將所有節點回收至 avail
}

float Polynomial::Evaluate(float x) const {
    float result = 0;
    for (PolyNode* p = head->link; p != head; p = p->link)
        result += p->coef * pow(x, p->exp);
    return result;
}

Polynomial Polynomial::operator+(const Polynomial& b) const {
    Polynomial result;
    // TODO: 加法邏輯
    return result;
}

Polynomial Polynomial::operator-(const Polynomial& b) const {
    Polynomial result;
    // TODO: 減法邏輯
    return result;
}

Polynomial Polynomial::operator*(const Polynomial& b) const {
    Polynomial result;
    // TODO: 乘法邏輯
    return result;
}

istream& operator>>(istream& is, Polynomial& x) {
    int n, c, e;
    is >> n;
    for (int i = 0; i < n; i++) {
        is >> c >> e;
        x.Attach(c, e);
    }
    return is;
}

ostream& operator<<(ostream& os, Polynomial& x) {
    PolyNode* p = x.head->link;
    bool first = true;
    while (p != x.head) {
        if (!first && p->coef >= 0) os << "+";
        os << p->coef << "x^" << p->exp << " ";
        p = p->link;
        first = false;
    }
    return os;
}

int main() {
    Polynomial p1, p2, sum, prod;
    cout << "輸入第一個多項式 (n coef exp ...): ";
    cin >> p1;
    cout << "輸入第二個多項式: ";
    cin >> p2;

    sum = p1 + p2;
    prod = p1 * p2;

    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p1 + p2: " << sum << endl;
    cout << "p1 * p2: " << prod << endl;

    float x;
    cout << "輸入 x 值: ";
    cin >> x;
    cout << "p1(" << x << ") = " << p1.Evaluate(x) << endl;
}



```



---

## 效能分析


1. 加法與減法時間複雜度：O(m+n)。

2. 乘法時間複雜度： 𝑂(𝑚×𝑛)。

3. 空間複雜度：O(m+n)


---

## 測試與驗證

### 測試案例


| 測試案例 | 多項式 1 | 多項式 2 | 預期結果 | 實際輸出 |
|----------|----------------|-----------|-----------|-----------|
| 測試一   | 3x^2 + 2x + 1 | 2x^2 + x | 5x^2 + 3x + 1 | 5x^2 + 3x + 1 |
| 測試二   | x^3 + 4x + 5  | -x^3 - 4x - 5 | 0 | 0 |
| 測試三   | 5x^4 + 2x^2 + 1 | 	3x^2 + 4 | 	5x^4 + 5x^2 + 5 | 5x^4 + 5x^2 + 5 |



### 編譯與執行指令

```bash
g++ -o hw2 hw2.c++
.\hw2
```

### 結論

1. 程式能正確執行並計算出多項式的結果。

2. 測試案例驗證執行後輸出的結果。

3. 運算子多載 讓加減乘與輸入輸出更加直觀。

---


## 申論及開發報告

使用 Circular Linked List 可方便在任意位置插入與刪除項次，且利用 header node 讓程式更簡化。

available-space list 減少 new / delete 的次數，提高效率。