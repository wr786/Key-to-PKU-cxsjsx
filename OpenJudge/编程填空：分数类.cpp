#include <iostream>
using namespace std;
int gcd(int x, int y){
	return x%y==0?y:gcd(y,x%y);
}
class Fraction
{
    int num, den;
public:
// 在此处补充你的代码
	Fraction(int n, int d=1): num(n), den(d) {}
	Fraction operator * (const Fraction& other) {
		int nn = num*other.num, nd = den*other.den;
		int dd = gcd(nn ,nd);
		nn /= dd; nd /= dd;
		return Fraction(nn, nd);
	}
	Fraction operator / (const Fraction& other) {
		int nn = num*other.den, nd = den*other.num;
		int dd = gcd(nn ,nd);
		nn /= dd; nd /= dd;
		return Fraction(nn, nd);
	}
	Fraction& operator *= (const Fraction& other) {return (*this) = (*this)*other;}
	Fraction& operator /= (const Fraction& other) {return (*this) = (*this)/other;}
	friend ostream& operator << (ostream& os, const Fraction& other) {
		os << other.num << "/" << other.den;
		return os;
	}
	operator float() {return num/(float)den;}
///////////////////
};
 
int main() {
	int a,b,c;
	cin >> a >> b >> c;
    Fraction f(a, b), g(c);
	f *= g;
	cout << f << endl;
	f /= g;
	cout << f << endl;
	f = f * f;
	cout << f << endl;
	f = f / g;
	cout << f << endl;
	cout << (float) f << endl;
    return 0;
}