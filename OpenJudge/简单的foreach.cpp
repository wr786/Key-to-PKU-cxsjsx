/**
 * @Date:   2020-02-19T11:55:14+08:00
 * @Last modified time: 2020-03-18T10:26:07+08:00
 */



#include <iostream>
#include <string>
using namespace std;
// 在此处补充你的代码
template<class T, class fun>
void MyForeach(T begin, T end, fun func) {
  for(; begin!=end; begin++)
    func(*begin);
}
void Print(string s)
{
	cout << s;
}
void Inc(int & n)
{
	++ n;
}
string array[100];
int a[100];
int main() {
	int m,n;
	while(cin >> m >> n) {
		for(int i = 0;i < m; ++i)
			cin >> array[i];
		for(int j = 0; j < n; ++j)
			cin >> a[j];
		MyForeach(array,array+m,Print);
		cout << endl;
		MyForeach(a,a+n,Inc);
		for(int i = 0;i < n; ++i)
			cout << a[i] << ",";
		cout << endl;
	}
	return 0;
}
