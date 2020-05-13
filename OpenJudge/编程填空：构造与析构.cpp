#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
// 在此处补充你的代码
class A{public:A(){cout<<"New A\n";}virtual ~A(){cout<<"Delete A\n";}};
class B:public A{public:B(){cout<<"New B\n";}~B(){cout<<"Delete B\n";}};
int main(){
	int n;
	cin >> n;
	for (int i = 1; i<=n; i++) {
		int x;
		cin >> x;
		if (x == 0) {
			A *a = new A();
			delete a;
		}else {
			A *a = new B();
			delete a;
		}
	}
	return 0;	
}