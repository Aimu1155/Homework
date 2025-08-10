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

