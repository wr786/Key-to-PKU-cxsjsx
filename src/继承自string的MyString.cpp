#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class MyString:public string
{
// 在此处补充你的代码
private:
	string s;
public:
	MyString(): s("") {}
	MyString(const char* _s): s(_s) {}
	MyString(const MyString& other): s(other.s) {}
	MyString(const string& _s): s(_s) {}
	friend ostream& operator << (ostream& os, const MyString& myStr) {
		os << myStr.s;
		return os;
	}
	MyString& operator = (const MyString& other) {
		s = other.s;
		return *this;
	}
	char& operator [] (const int& index) {
		return s[index];
	}
	MyString operator + (const MyString& other) {
		return MyString(s + other.s);
	}
	MyString operator + (const char* cs) {
		return *this + MyString(cs);
	}
	friend MyString operator + (const char* cs, const MyString& myStr) {
		return MyString(cs) + myStr;
	}
	bool operator < (const MyString& other) {
		return s < other.s;
	}
	string operator () (int startpos, int len) {
		return s.substr(startpos, len);
	}
	MyString& operator += (const char* cs) {
		s = s + string(cs);
		return *this;
	}
};


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
        sort(SArray,SArray+4);
	for( int i = 0;i < 4;i ++ )
	cout << SArray[i] << endl;
	//s1的从下标0开始长度为4的子串
	cout << s1(0,4) << endl;
	//s1的从下标5开始长度为10的子串
	cout << s1(5,10) << endl;
	return 0;
}
