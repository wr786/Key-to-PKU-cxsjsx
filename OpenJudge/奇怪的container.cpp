#include <iostream>
#include <string>
using namespace std;
template <class T> 
class container{
private:
	T data;
public:
	container(T t): data(t) {}
	container& operator = (const container& other) {data = other.data; return *this;}
	container operator + (const container& other)  {return data + other.data + other.data;}
	container operator + (const T& other) {return data + other;}
	friend ostream& operator << (ostream& os, const container& other) {os << other.data; return os;}
};
int main(){
	int n,m;
	cin >> n >> m;
	string s1,s2;
	cin >> s1 >> s2;
    container <int> a = n;
    container <int> b = m;
    cout<<a+b<<endl;
    cout<<a+m<<endl;
    container <string> sa = string(s1);
    container <string> sb = string(s2);
    cout<<sa+sb<<endl;
    cout<< sa + s2<<endl;
}