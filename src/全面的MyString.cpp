#include <cstdlib>
#include <iostream>
using namespace std;
int strlen(const char * s)
{	int i = 0;
	for(; s[i]; ++i);
	return i;
}
void strcpy(char * d,const char * s)
{
	int i = 0;
	for( i = 0; s[i]; ++i)
		d[i] = s[i];
	d[i] = 0;

}
int strcmp(const char * s1,const char * s2)
{
	for(int i = 0; s1[i] && s2[i] ; ++i) {
		if( s1[i] < s2[i] )
			return -1;
		else if( s1[i] > s2[i])
			return 1;
	}
	return 0;
}
void strcat(char * d,const char * s)
{
	int len = strlen(d);
	strcpy(d+len,s);
}
class MyString
{
// 在此处补充你的代码
private:
	char* s;
public:
	MyString():s(NULL){}
	MyString(const char* _s) {
		if(_s) {
			s  = new char[strlen(_s)+1];
			strcpy(s, _s);
		}
	}
	MyString& operator = (const MyString& other) {
		if(&other == this) return *this;
		if(other.s) {
			s = new char[strlen(other.s)+1];
			strcpy(s, other.s);
		} else {
			s = NULL;
		}
		return *this;
	}
	MyString& operator = (const char* str) {
		*this = MyString(str);
		return *this;
	}
	bool operator < (const MyString& other) {
		return strcmp(s, other.s) == -1;
	}
	bool operator > (const MyString& other) {
		return strcmp(s, other.s) == 1;
	}
	bool operator == (const MyString& other) {
		return !strcmp(s, other.s);
	}
	friend ostream& operator << (ostream& os, const MyString& S) {
		if(S.s) os << S.s;
		return os;
	}
	MyString operator + (const MyString& other) {
		MyString tmp;
		tmp.s = new char[strlen(s) + strlen(other.s) + 1];
		strcpy(tmp.s, s);
		strcat(tmp.s, other.s);
		return tmp;
	}
	MyString operator + (const char* str) {
		return (*this + MyString(str));
	}
	friend MyString operator + (const char* str, const MyString& myStr) {
		return (MyString(str) + myStr);
	}
	MyString operator () (int l, int r) {
		if(l < 0) l = 0;
		r = l + r; // 刚开始把r当成结束位置了
		if(r > strlen(s)) r = strlen(s);
		char * tmp = new char[r - l + 1];
		for(int i=0; i<r-l; i++)
			tmp[i] = s[l+i];
		tmp[r] = 0;
		return MyString(tmp);
	}
 	char& operator [] (const int& idx) {
		return s[idx];
	}
	MyString& operator += (const char* str) {
		*this = *this + MyString(str);
		return *this;
	}
	MyString& operator += (const MyString& other) {
		*this = *this + other;
		return *this;
	}
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
