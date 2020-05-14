#define _GLIBCXX_USE_CXX11_ABI 0
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;
// 在此处补充你的代码
class MyString {
private:
	string data;
public:
	MyString(): data("") {}
	MyString(const char* c): data(string(c)) {}
	MyString(string str): data(str) {}
	MyString(const MyString& other): data(other.data) {}
	friend ostream& operator << (ostream& os, MyString s) {
		os << s.data;
		return os;
	}
	friend MyString operator + (const MyString& self, const MyString& other) {return self.data + other.data;}
	// MyString operator + (const char* other) {return data + other;}
	MyString& operator += (const MyString& other) {data = data + other.data; return *this;}
	char& operator [] (int idx) {return data[idx];}
	MyString operator () (int l, int len) {return data.substr(l, len);}
	bool operator < (const MyString& other) {return data < other.data;}
	bool operator == (const MyString& other) {return data == other.data;}
	bool operator > (const MyString& other) {return data > other.data;}
};

int CompareString( const void * e1, const void * e2)
{
	MyString * s1 = (MyString * ) e1;
	MyString * s2 = (MyString * ) e2;
	if( * s1 < *s2 )
		return -1;
	else if( *s1 == *s2)
		return 0;
	else if( *s1 > *s2 )
		return 1;
}
int main()
{
	MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
	MyString SArray[4] = {"big","me","about","take"};
	cout << "1. " << s1 << s2 << s3<< s4<< endl;
	s4 = s3;
	s3 = s1 + s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A' ;
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;
	qsort(SArray,4,sizeof(MyString),CompareString);
	for( int i = 0;i < 4;i ++ )
	cout << SArray[i] << endl;
	//s1的从下标0开始长度为4的子串
	cout << s1(0,4) << endl;
	//s1的从下标5开始长度为10的子串
	cout << s1(5,10) << endl;
	return 0;
}