#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;
const int MAX = 110;
class CHugeInt {
// 在此处补充你的代码
private:
	string str;
public:
	CHugeInt(const char* s):str(s) {}
	CHugeInt(const int& x):str(to_string(x)) {}
	CHugeInt(const string& s):str(s) {}
	CHugeInt(const CHugeInt& other):str(other.str) {}
	friend ostream& operator << (ostream& os, const CHugeInt& CHI) {
		os << CHI.str;
		return os;
	}
	CHugeInt operator + (const CHugeInt& other) {
		string a = this->str, b = other.str;
		int la = a.length(), lb = b.length();
		if(la < lb) {
			swap(la, lb);
			swap(a, b);
		} // la >= lb
		int updigit = 0;
		for(int i=1; i<=lb; i++) {
			int pa = la - i, pb = lb - i;
			a[pa] = a[pa] - '0' + b[pb] - '0' + updigit;
			updigit = a[pa] / 10;
			a[pa] %= 10;
			a[pa] += '0';
		}
		int cur = la - lb - 1;
		while(updigit && cur>= 0) {
			a[cur] = a[cur] - '0' + updigit;
			updigit = a[cur] / 10;
			a[cur] %= 10;
			a[cur] += '0';
			cur--;
		}
		if(updigit) {a = to_string(updigit) + a;}
		return CHugeInt(a);
	}
	CHugeInt operator + (const int& other) {
		return *this + CHugeInt(other);
	}
	friend CHugeInt operator + (const int& other, const CHugeInt& CHI) {
		return CHugeInt(other) + CHI;
	}
	void operator += (const int& other) {
		*this = *this + CHugeInt(other);
	}
	friend CHugeInt& operator ++ (CHugeInt& CHI) {
		CHI = CHI + 1;
		return CHI;
	}
	friend CHugeInt operator ++ (CHugeInt& CHI, int x) {
		CHugeInt tmp(CHI);
	 	CHI = CHI + 1;
		return tmp;
	}
};
int  main()
{
	char s[210];
	int n;

	while (cin >> s >> n) {
		CHugeInt a(s);
		CHugeInt b(n);

		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout  << ++ b << endl;
		cout << b++ << endl;
		cout << b << endl;
	}
	return 0;
}
