#include <iostream>
using namespace std;

class A {
public:
// 在此处补充你的代码
	int data;
	A(int t=0): data(t) {}
	A(const A& other) {data = other.data;}
	A& operator -= (const A& other) {
		data -= other.data;
		return *this;
	}
	A& operator += (const A& other) {
		data += other.data;
		return *this;
	}
	int& getValue() {return data;}
	friend ostream& operator << (ostream& os, const A& a) {
		os << a.data;
		return os;
	}
};

int main() {
	int t;
	cin >> t;
	while(t-- ) {
		int m,n,k;
		cin >> m >> n >> k;	
	    A a(m);
	    A b = a;
	    cout << b << endl;
	    cout << (a += b -= n) << endl;
	    cout << a.getValue() << endl;
	    a.getValue() = k;
	    cout << a << endl;
	} 
	return 0;
}