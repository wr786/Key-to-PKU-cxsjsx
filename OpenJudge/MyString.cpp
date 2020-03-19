#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class MyString {
	char * p;
public:
	MyString(const char * s) {
		if( s) {
			p = new char[strlen(s) + 1];
			strcpy(p,s);
		}
		else
			p = NULL;

	}
	~MyString() { if(p) delete [] p; }
// 在此处补充你的代码
	void Copy(const char* s) {
		if(s) {
			p = new char[strlen(s) + 1];
			strcpy(p,s);
		}
		else
			p = NULL;
	}
	MyString& operator = (const MyString & other) {
		if(other.p) {
			p = new char[strlen(other.p) + 1];
			strcpy(p, other.p);
		} else {
			p = NULL;
		}
		return (*this);
	}
	MyString& operator = (const char* s) {
		if(s) {
			p = new char[strlen(s) + 1];
			strcpy(p,s);
		}
		else
			p = NULL;
		return (*this);
	}
	friend ostream& operator << (ostream& os, const MyString& myStr) {
		os << myStr.p;
		return os;
	}
};
int main()
{
	char w1[200],w2[100];
	while( cin >> w1 >> w2) {
		MyString s1(w1),s2 = s1;
		MyString s3(NULL);
		s3.Copy(w1);
		cout << s1 << "," << s2 << "," << s3 << endl;

		s2 = w2;
		s3 = s2;
		s1 = s3;
		cout << s1 << "," << s2 << "," << s3 << endl;

	}
}
