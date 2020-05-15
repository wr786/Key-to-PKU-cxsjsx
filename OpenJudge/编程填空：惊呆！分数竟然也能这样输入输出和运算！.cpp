#include <iostream>
using namespace std;
int gcd(int a, int b) { // 计算两个数的最大公约数
    return (!b) ? a : gcd(b, a % b);
}
class Fraction {
    int p, q;
public:
	Fraction(int _p=0, int _q=1):p(_p),q(_q) {}
	friend istream& operator >> (istream& is, Fraction& f) {
		is >> f.p >> f.q;
		int div = gcd(f.p, f.q);
		f.p /= div;
		f.q /= div;
		return is;
	}
	friend ostream& operator << (ostream& os, const Fraction& f) {
		
		os << f.p ;
		if(f.q != 1) os <<  "/" << f.q;
		return os;
	}
	Fraction operator * (const Fraction& other) {
		int np = p*other.p, nq= q*other.q;
		int div=gcd(np,nq);
		np/=div; nq/=div;
		return Fraction(np,nq);
	}
};

int main(){
    int testcases;
    cin >> testcases;
    while (testcases --) {
        Fraction a, b, two(2);
        cin >> a >> b;
        cout << a << " * " << b << " = " << a * b << endl;
        cout << "2 * " << a << " = " << two * a << endl;
        cout << b << " * 3 = " << b * 3 << endl;
    }
    return 0;
}