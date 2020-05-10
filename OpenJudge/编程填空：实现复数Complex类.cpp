#include <iostream>
using namespace std;
// 在此处补充你的代码
class Complex {
private:
	int RE;
	int IM;
public:
	Complex(int r=0, int i=0): RE(r), IM(i) {}
	Complex(const char* str) {
		RE = str[0] - '0';
		IM = str[2] - '0';
	}
	friend ostream& operator << (ostream& os, const Complex& c) {
		bool hasRe = c.RE != 0, hasIm = c.IM != 0;
		if(hasRe) os << c.RE;
		if(hasRe && hasIm) os << "+";
		if(hasIm) os << c.IM << "i";
		if(!hasRe && !hasIm) os << 0;
		return os;
	}
	Complex operator + (const Complex& other) {
		return Complex(RE+other.RE, IM+other.IM);
	}
	Complex operator - (const Complex& other) {
		return Complex(RE-other.RE, IM-other.IM);
	}
	Complex operator * (const Complex& other) {
		return Complex(RE*other.RE-IM*other.IM, RE*other.IM+IM*other.RE);
	}
	Complex& operator += (const Complex& other) {
		*this = *this + other;
		return *this;
	}
	Complex& operator -= (const Complex& other) {
		*this = *this - other;
		return *this;
	}
	Complex& operator *= (const Complex& other) {
		*this = *this * other;
		return *this;
	}
};

int main() {
	Complex c1;
	Complex c2("3+2i"); // 用字符串初始化时，只需考虑"a+bi"的形式，其中a和b都是1位数字
	Complex c3(c2);
	Complex c4(-15);
	cout << c2 << endl;
	cout << c3 << endl;
	cout << c4 << endl;
	cout << c2 + c4 << endl;
	cout << c2 - c3 << endl;
	cout << c2 * c3 << endl;
	c2 += c4;
	cout << c2 << endl;
	c2 -= -12;
	cout << c2 << endl;
	c3 *= c3;
	cout << c3 << endl;
	return 0;
}