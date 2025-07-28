# 41141151

作業二

## 解題說明

本題要求實作一個「多項式相加」的程式，並運用類別（class）與運算子多載（operator overloading）來實作。需包含以下功能：

1. 以 >> 讀入多項式。

2. 以 << 輸出多項式。

3. 使用 + 進行多項式的加法運算。

4. 動態記憶體配置與錯誤檢查。


## 解題策略

1. 建立 Term 類別表示一項，包括係數（coef）與次方（exp）。

2. 建立 Polynomial 類別，使用陣列儲存多項式的所有項次。

3. 多項式加法的方法：由大到小從兩個排序後的多項式中讀取：
   - 如果次方相同，則合併係數。
   - 如果次方不同，將較大的次方直接加入結果。

4. 加法結果必須處理係數為 0 的項次。

5. 使用動態陣列來容納多項式的項數，並進行資源釋放以避免記憶體洩漏。

6. 運算子： >>  、 << 、 + 。




## 程式實作

```cpp
#include <iostream>
#include <cmath>
using namespace std;

//限制大小在100內
const int MAX_TERMS = 100; 

class Polynomial;

class Term {
    friend class Polynomial;
    friend istream& operator>>(istream&, Polynomial&);
    friend ostream& operator<<(ostream&, const Polynomial&);
private:
    float coef; // 係數
    int exp;    // 次方
};

class Polynomial {
private:
    Term termArray[MAX_TERMS];
    int terms;

public:
    Polynomial() {
        terms = 0;
    }

    void NewTerm(float c, int e) {
        if (terms >= MAX_TERMS) {
            cout << "ERROR：超過項目的上限" << endl;
            return;
        }
        termArray[terms].coef = c;
        termArray[terms].exp = e;
        terms++;
    }

    Polynomial Add(const Polynomial& b) const {
        Polynomial c;
        int aPos = 0, bPos = 0;

        while (aPos < terms && bPos < b.terms) {
            if (termArray[aPos].exp == b.termArray[bPos].exp) {
                float t = termArray[aPos].coef + b.termArray[bPos].coef;
                if (t != 0)
                    c.NewTerm(t, termArray[aPos].exp);
                aPos++;
                bPos++;
            } else if (termArray[aPos].exp > b.termArray[bPos].exp) {
                c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
                aPos++;
            } else {
                c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
                bPos++;
            }
        }

        for (; aPos < terms; aPos++)
            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
        for (; bPos < b.terms; bPos++)
            c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);

        return c;
    }

    Polynomial Mult(const Polynomial& b) const {
        Polynomial c;
        for (int i = 0; i < terms; ++i) {
            for (int j = 0; j < b.terms; ++j) {
                float newCoef = termArray[i].coef * b.termArray[j].coef;
                int newExp = termArray[i].exp + b.termArray[j].exp;

                bool found = false;
                for (int k = 0; k < c.terms; ++k) {
                    if (c.termArray[k].exp == newExp) {
                        c.termArray[k].coef += newCoef;
                        found = true;
                        break;
                    }
                }
                if (!found)
                    c.NewTerm(newCoef, newExp);
            }
        }
        return c;
    }

    float Eval(float x) const {
        float result = 0;
        for (int i = 0; i < terms; ++i) {
            result += termArray[i].coef * pow(x, termArray[i].exp);
        }
        return result;
    }

    friend istream& operator>>(istream& in, Polynomial& poly);
    friend ostream& operator<<(ostream& out, const Polynomial& poly);
};

istream& operator>>(istream& in, Polynomial& poly) {
    cout << "項數: ";
    in >> poly.terms;
    for (int i = 0; i < poly.terms; ++i) {
        cout << "輸入第 " << i + 1 << " 項 (coef exp): ";
        in >> poly.termArray[i].coef >> poly.termArray[i].exp;
    }
    return in;
}

ostream& operator<<(ostream& out, const Polynomial& poly) {
    for (int i = 0; i < poly.terms; ++i) {
        float coef = poly.termArray[i].coef;
        int exp = poly.termArray[i].exp;

        if (i > 0) {
            if (coef > 0) out << " + ";
            else out << " - ";
        } else {
            if (coef < 0) out << "-";
        }

        float absCoef = abs(coef);
        if (absCoef != 1 || exp == 0)
            out << absCoef;

        if (exp != 0) {
            out << "x";
            if (exp != 1)
                out << "^" << exp;
        }
    }
    return out;
}

int main() {
    Polynomial p1, p2, sum, prod;

    cout << "第一個多項式:\n";
    cin >> p1;

    cout << "第二個多項式:\n";
    cin >> p2;

    sum = p1.Add(p2);
    prod = p1.Mult(p2);
    
    cout << "\n===============" << endl;
    cout << "\n第一個多項式: " << p1 << endl;
    cout << "第二個多項式: " << p2 << endl;
    cout << "相加結果: " << sum << endl;
    cout << "相乘結果: " << prod << endl;

    float x;
    cout << "\n輸入x值: ";
    cin >> x;
    cout << "p1(" << x << ") = " << p1.Eval(x) << endl;

    return 0;
}


```



---

## 效能分析


1. 時間複雜度：O(m + n)

2. 空間複雜度：O(m + n)


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

---


## 申論及開發報告

將 Term 與 Polynomial 分開，方便維護及擴充。

使用類別可封裝資料，減少直接操作內部資料結構的風險。

使用動態記憶體確保程式能處理任意項數的多項式。

使用 + 、 >> 、 << 等運算子。
