#include <iostream>
#include <iterator>
using namespace std;

template<class T1, class T2>
void Copy(T1 s, T1 e, T2 x) {
    for(; s != e; ++s, ++x)
        *x = *s;
}
class Fib {
private:
	int idx;
public:
	Fib(int d): idx(d) {}
	Fib(const Fib& other) {idx = other.idx;}
	int operator * () {
		int a=1, b=1, c=1;
		for(int i=3; i<=idx; i++) {
			c = a+b;
			a = b;
			b = c;
		}
		return c;
	}
	Fib& operator ++ () {return (*this) = idx+1;}
	bool operator == (const Fib& other) {return idx==other.idx;}
	bool operator != (const Fib& other) {return !((*this) == other);}
};
int main() {
	while(true) {
		int n;
		cin >> n;
		if(n == 0)
			break;
		
	    Fib f1(1), f2(n);
	    ostream_iterator<int> it(cout, " ");
	    Copy(f1, f2, it);
	    cout << endl;
	}
	return 0;
}