#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
class A {public:int age; A(int a):age(a){} virtual char getName(){return 'A';}};
class B: public A {public:B(int a):A(a){} char getName(){return 'B';}};
class Comp {
public:
	bool operator () (const A* a, const A* b) const {
		return a->age < b->age;
	}
};
void Print(A* x) {
	cout << x->getName() << " " << x->age << endl;
}
int main()
{

	int t;
	cin >> t;
	set<A*,Comp> ct;
	while( t -- ) {
		int n;
		cin >> n;
		ct.clear();
		for( int i = 0;i < n; ++i)	{
			char c; int k;
			cin >> c >> k;
			
			if( c == 'A')
				ct.insert(new A(k));
			else
				ct.insert(new B(k));
		}	
		for_each(ct.begin(),ct.end(),Print);
		cout << "****" << endl;
	}
}