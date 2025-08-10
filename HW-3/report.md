# 41141151

作業三

## 解題說明

本題要求實作一個多項式類別，用 Circular Linked List with Header Node 來儲存多項式的每一項，需要有：

1. 以 >> 讀入多項式並建立鏈結串列。

2. 以 << 輸出多項式。

3. 使用 +、-、* 進行多項式的加減乘運算。

4. 計算多項式在特定的值。

5. 建構子、指定運算子與解構子。

6. 使用 available-space list 節點回收。


## 解題策略

1. 建立 PolyNode 結構儲存係數、指數與下一個節點指標：
    coef | exp | link

2. 使用 Circular Linked List with Header Node 來儲存多項式，Header Node不存放東西。

3. 使用 Evaluate 代入數值計算多項式。




## 程式實作

```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Polynomial;

// 用來存放多項式
class Term {
    friend class Polynomial;
private:
    float coef, exp;   // 係數與指數
    Term* link;        // 指向下一個節點
    Term(float c, int e, Term* next = nullptr) : coef(c), exp(e), link(next) { }
    
public:
    float getCoef() const { return coef; }
    int getExp() const { return exp; }
    Term* getLink() const { return link; }
    void setLink(Term* next) { link = next; }
    void setCoef(float c) { coef = c; }
};

class Polynomial {
private:
    Term* head;                // header node
    static Term* avail;        //available-space list

    // 取得一個新節點，如果 avail 有節點就拿來用，否則 new 一個
    Term* GetNode(float c, int e, Term* next) {
        Term* p;
        if (avail == nullptr) {
            p = new Term(c, e, next); // 沒有回收節點，直接 new
        } else {
            p = avail;                // 從 avail 取出節點
            avail = avail->getLink();
            p->setCoef(c);
            p->setLink(next);
        }
        return p;
    }

    void RetNode(Term* x) {
        x->setLink(avail);
        avail = x;
    }

    void Clear() {
        if (head == nullptr) return;
        Term* current = head->getLink();
        while (current != head) {
            Term* temp = current;
            current = current->getLink();
            RetNode(temp);
        }
        RetNode(head);
        head = nullptr;
    }

public:
    Polynomial() : head(nullptr) {}
    
    // 複製
    Polynomial(const Polynomial& a) : head(nullptr) {
        if (a.head == nullptr) return;
        head = GetNode(0, -1, nullptr);
        head->setLink(head);
        Term* current = a.head->getLink();
        while (current != a.head) {
            Insert(current->getCoef(), current->getExp());
            current = current->getLink();
        }
    }
    
    const Polynomial& operator=(const Polynomial& a) {
        if (this != &a) {
            Clear();
            if (a.head != nullptr) {
                head = GetNode(0, -1, nullptr);
                head->setLink(head);
                Term* current = a.head->getLink();
                while (current != a.head) {
                    Insert(current->getCoef(), current->getExp());
                    current = current->getLink();
                }
            }
        }
        return *this;
    }
    
    // 解構子
    ~Polynomial() {
        Clear();
    }
    
    // 插入一項
    void Insert(float c, int e) {
        if (head == nullptr) {
            head = GetNode(0, -1, nullptr);
            head->setLink(head);
            head->setLink(GetNode(c, e, head));
            return;
        }
        Term* prev = head;
        Term* current = head->getLink();
        
        while (current != head && current->getExp() > e) {
            prev = current;
            current = current->getLink();
        }
        if (current != head && current->getExp() == e) {
            current->setCoef(current->getCoef() + c);
            if (current->getCoef() == 0) { // 如果係數為 0，刪除節點
                prev->setLink(current->getLink());
                RetNode(current);
            }
        } else {
            // 插入新節點
            prev->setLink(GetNode(c, e, current));
        }
    }
    
    // 多項式加法
    Polynomial operator+(const Polynomial& b) const {
        Polynomial result;
        Term* aCurrent = (head == nullptr) ? nullptr : head->getLink();
        Term* bCurrent = (b.head == nullptr) ? nullptr : b.head->getLink();
        while ((aCurrent != nullptr && aCurrent != head) || 
               (bCurrent != nullptr && bCurrent != b.head)) {
                   
            float coef = 0;
            int exp = 0;
            
            if (aCurrent != nullptr && aCurrent != head && 
                (bCurrent == nullptr || bCurrent == b.head || aCurrent->getExp() > bCurrent->getExp())) {
                coef = aCurrent->getCoef();
                exp = aCurrent->getExp();
                aCurrent = aCurrent->getLink();
            } else if (bCurrent != nullptr && bCurrent != b.head && 
                       (aCurrent == nullptr || aCurrent == head || bCurrent->getExp() > aCurrent->getExp())) {
                coef = bCurrent->getCoef();
                exp = bCurrent->getExp();
                bCurrent = bCurrent->getLink();
            } else {
                coef = aCurrent->getCoef() + bCurrent->getCoef();
                exp = aCurrent->getExp();
                aCurrent = aCurrent->getLink();
                bCurrent = bCurrent->getLink();
            }
            if (coef != 0) result.Insert(coef, exp);
        }
        return result;
    }
    
    // 多項式減法
    Polynomial operator-(const Polynomial& b) const {
        Polynomial result;
        Term* aCurrent = (head == nullptr) ? nullptr : head->getLink();
        Term* bCurrent = (b.head == nullptr) ? nullptr : b.head->getLink();
        while ((aCurrent != nullptr && aCurrent != head) || 
               (bCurrent != nullptr && bCurrent != b.head)) {
            float coef = 0;
            int exp = 0;
            if (aCurrent != nullptr && aCurrent != head && 
                (bCurrent == nullptr || bCurrent == b.head || aCurrent->getExp() > bCurrent->getExp())) {
                coef = aCurrent->getCoef();
                exp = aCurrent->getExp();
                aCurrent = aCurrent->getLink();
            } else if (bCurrent != nullptr && bCurrent != b.head && 
                       (aCurrent == nullptr || aCurrent == head || bCurrent->getExp() > aCurrent->getExp())) {
                coef = -bCurrent->getCoef();
                exp = bCurrent->getExp();
                bCurrent = bCurrent->getLink();
            } else {
                coef = aCurrent->getCoef() - bCurrent->getCoef();
                exp = aCurrent->getExp();
                aCurrent = aCurrent->getLink();
                bCurrent = bCurrent->getLink();
            }
            if (coef != 0) result.Insert(coef, exp);
        }
        return result;
    }
    
    // 多項式乘法
    Polynomial operator*(const Polynomial& b) const {
        Polynomial result;
        if (head == nullptr || b.head == nullptr) return result;
        Term* aCurrent = head->getLink();
        while (aCurrent != head) {
            Term* bCurrent = b.head->getLink();
            while (bCurrent != b.head) {
                float coef = aCurrent->getCoef() * bCurrent->getCoef();
                int exp = aCurrent->getExp() + bCurrent->getExp();
                result.Insert(coef, exp); // 插入並自動合併同次方
                bCurrent = bCurrent->getLink();
            }
            aCurrent = aCurrent->getLink();
        }
        return result;
    }
    
    // 計算x
    float Evaluate(float x) const {
        float result = 0;
        if (head == nullptr) return result;
        Term* current = head->getLink();
        while (current != head) {
            result += current->getCoef() * pow(x, current->getExp());
            current = current->getLink();
        }
        return result;
    }
    
    // 輸入與輸出運算子
    friend istream& operator>>(istream& is, Polynomial& x);
    friend ostream& operator<<(ostream& os, const Polynomial& x);
};

Term* Polynomial::avail = nullptr;

// 多項式輸入
istream& operator>>(istream& is, Polynomial& x) {
    x.Clear();
    int n;
    is >> n;
    if (n > 0) {
        x.head = x.GetNode(0, -1, nullptr);
        x.head->setLink(x.head);
        for (int i = 0; i < n; i++) {
            float coef;
            int exp;
            is >> coef >> exp;
            x.Insert(coef, exp);
        }
    }
    return is;
}

// 多項式輸出
ostream& operator<<(ostream& os, const Polynomial& x) {
    if (x.head == nullptr || x.head->getLink() == x.head) {
        os << "0";
        return os;
    }
    Term* current = x.head->getLink();
    bool firstTerm = true;
    while (current != x.head) {
        if (!firstTerm && current->getCoef() > 0) os << "+";
        if (current->getExp() == 0) {
            os << current->getCoef();
        } else {
            if (current->getCoef() != 1 && current->getCoef() != -1) {
                os << current->getCoef();
            } else if (current->getCoef() == -1) {
                os << "-";
            }
            os << "x";
            if (current->getExp() != 1) os << "^" << current->getExp();
        }
        firstTerm = false;
        current = current->getLink();
    }
    return os;
}

int main() {
    Polynomial p1, p2;
    cout << "第一個多項式: ";
    cin >> p1;
    cout << "第二個多項式: ";
    cin >> p2;

    cout << "\n第一個多項式為: " << p1 << endl;
    cout << "第二個多項式為: " << p2 << endl;

    Polynomial sum = p1 + p2;
    cout << "總和: " << sum << endl;

    Polynomial diff = p1 - p2;
    cout << "差分: " << diff << endl;

    Polynomial product = p1 * p2;
    cout << "乘積: " << product << endl;

    float x;
    cout << "\n輸入 x 值: ";
    cin >> x;
    cout << "p1(" << x << ") = " << p1.Evaluate(x) << endl;
    cout << "p2(" << x << ") = " << p2.Evaluate(x) << endl;

    return 0;
}


```



---

## 效能分析


1. 加法減法時間複雜度：O(m+n)。

2. 乘法時間複雜度： 𝑂(𝑚×𝑛)。

3. 空間複雜度：O(m+n)


---

## 測試與驗證

### 測試案例


| 測試案例 | 輸入多項式 1 | 輸入多項式 2 | 第一個多項式/第二個多項式 | 預期結果與實際輸出 (總和/差分/乘積) |
|----------|----------------|-----------|-----------|-----------|
| 測試一   | 3 3 2 2 1 1 0 | 2 2 2 1 1 | 3x^2 + 2x + 1 / 2x^2 + x | 5x^2+3x+1 / x^2+x+1 / 6x^4+7x^3+4x^2+x |
| 測試二   | 3 1 3 4 1 5 0  | 3 -1 3 -4 1 -5 0 | x^3 + 4x + 5 / -x^3 - 4x - 5 | 0 / 2x^3 + 8x + 10 / -x^6 - 8x^4 - 10x^3 -1 6x^2 - 40x - 25 |
| 測試三   | 3 5 4 2 2 1 0 | 2 3 2 4 0 | 5x^4 + 2x^2 + 1 / 3x^2 + 4 | 5x^4 + 5x^2 + 5 / 5x^4 - x^2 - 3 / 15x^6 + 26x^4+  11x^2 + 4 |



### 編譯與執行指令

```bash
g++ -o hw3 HW-3.cpp
.\hw3
```

### 結論

1. 程式能正確執行並計算出多項式的結果。

2. 測試案例與執行後輸出的結果一致。

3. 這個程式完整有多項式的加法、減法和乘法運算。

---


## 申論及開發報告

使用 Circular Linked List 可方便在任意位置插入與刪除項次，且利用 header node 讓程式更簡化。

available-space list 減少 new / delete 的次數，提高效率。

將多項式封裝為Polynomial，項封裝為Term。
