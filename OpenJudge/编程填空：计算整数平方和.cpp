#include <iostream>
using namespace std;
// 在此处补充你的代码
class CType {
public:
	int val;
	CType(int v=0): val(v){}
	void setvalue(int v) { val = v;}
	friend ostream& operator << (ostream& os, const CType& c) {
		os << c.val;
		return os;
	}
	CType operator ++ (int x) {int tmp = val; val = val*val; return tmp;}
};
int main(int argc, char* argv[]) {
	CType obj;
	int   n;		
	cin>>n;
	while ( n ) {
		obj.setvalue(n);
		cout<<obj++<<" "<<obj<<endl;
		cin>>n;
	}
	return 0;
}