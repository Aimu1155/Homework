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
