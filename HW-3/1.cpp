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

