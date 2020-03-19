#include <iostream>
using namespace std;
class MyInt
{
	int nVal;
	public:
	MyInt( int n) { nVal = n ;}
// 在此处补充你的代码
	MyInt& operator - (int x) {
		nVal -= x;
		return *this;
	}
	operator int () {
		return nVal;
	}
};
int Inc(int n) {
	return n + 1;
}
int main () {
	int n;
	while(cin >>n) {
		MyInt objInt(n);
		objInt-2-1-3;
		cout << Inc(objInt);
		cout <<",";
		objInt-2-1;
		cout << Inc(objInt) << endl;
	}
	return 0;
}
