#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
// 在此处补充你的代码
template<typename T, int size>
class A {
public:
	T* data;
	A() {data = new T[size];}
	A(const T* array) {
		data = new T[size];
		for(int i=0; i<size; i++)
			data[i] = array[i];
	}
	template<typename T2>
	T2 sum(int beg, int end, T2(*fn)(T)) {
		T2 ret = fn(data[beg]);
		for(int i=beg+1; i<=end; i++)
			ret += fn(data[i]);
		return ret;
	}
};
string int2string(int x) { return to_string(x); }
int int2squareint(int x) { return x * x; }

int string2int(string str) {
	int res = 0;
	for (string::iterator iter = str.begin(); iter != str.end(); ++iter)
		res += *iter;
	return res;
}
string string2longerstring(string str) { return str + str; }

int main() {

	int t;
	cin >> t;
	while (t--) {
		int b1[10];
		for (int i = 0; i < 10; ++i)

			cin >> b1[i];
		A<int, 10> a1 = b1;
		cout << a1.sum(2, 6, int2squareint) << endl;
		cout << a1.sum(2, 6, int2string) << endl;

		string b2[4];
		for (int i = 0; i < 4; ++i)
			cin >> b2[i];

		A<string, 4> a2 = b2;
		cout << a2.sum(0, 3, string2int) << endl;
		cout << a2.sum(0, 3, string2longerstring) << endl;
	}
	return 0;
}