#include <iostream>
using namespace std;
class A {
public:
	int val;

	A(int
			_val = 123):val(_val) {}
	A(const A & other) {val = other.val;}
	A& GetObj() {return *this;}
};
int main()
{
	int m,n;
	A a;
	cout << a.val << endl;
	while(cin >> m >> n) {
		a.GetObj() = m;
		cout << a.val << endl;
		a.GetObj() = A(n);
		cout << a.val<< endl;
	}
	return 0;
}
