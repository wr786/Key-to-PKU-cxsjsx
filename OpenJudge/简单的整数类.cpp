#include <stdio.h>
#include <iostream>
using namespace std;
class MyNum{
public:
    char C;
    MyNum(char c='0'): C(c) {}
MyNum operator * (const MyNum& other) const {
		return (C-'0') * (other.C - '0') + '0';
	}
	operator int() const {return C - '0';}
};

int main() { 
    char m,n;
    cin >> m >>  n;
    MyNum n1(m), n2(n);
    MyNum n3;
    n3 = n1*n2;
    cout << int(n3) << endl;
    return 0;
}