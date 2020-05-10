#include <iostream>
#include <set>
using namespace std;
// 在此处补充你的代码
class Rectangle {
private:
	int sideA;
	int sideB;
public:
	Rectangle(int a=0, int b=0): sideA(a), sideB(b) {}
	int getS() const {return sideA * sideB;}
	int getC() const {return 2*(sideA + sideB);}
	friend ostream& operator << (ostream& os, const Rectangle& r) {
		os << r.getS() << " " << r.getC();
		return os;
	}
	bool operator < (const Rectangle& other) const {
		if(getS() != other.getS()) return getS() > other.getS();
		return getC() > other.getC();
	}
};

class Comp {
public:
	bool operator () (const Rectangle& A, const Rectangle& B) const {
		if(A.getC() != B.getC()) return A.getC() < B.getC();
		return A.getS() < B.getS();
	}
};

int main() {
    multiset<Rectangle> m1;
    multiset<Rectangle, Comp> m2;
    int n, a, b;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a >> b;
        m1.insert(Rectangle(a, b));
        m2.insert(Rectangle(a, b));
    }
    for (multiset<Rectangle>::iterator it = m1.begin(); it != m1.end(); it++) {
        cout << *it << endl;
    }
    cout << endl;
    for (multiset<Rectangle>::iterator it = m2.begin(); it != m2.end(); it++) {
        cout << *it << endl;
    }
	return 0;
}