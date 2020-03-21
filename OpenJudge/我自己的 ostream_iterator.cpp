#include <iostream>
#include <list>
#include <string>
using namespace std;

template <class T1,class T2>
void Copy(T1 s,T1 e, T2 x)
{
    for(; s != e; ++s,++x)
        *x = *s;
}


template<class T>
class myostream_iteraotr
{
// 在此处补充你的代码
private:
    ostream& os;
    T data;
    string separator;
public:
    myostream_iteraotr(ostream& o, const char* s):separator(s), data(), os(o) {}
    myostream_iteraotr(myostream_iteraotr& other):os(other.os), data(other.data), separator(other.separator) {}
    T& operator * () {
        return data;
    }
    friend void operator ++ (myostream_iteraotr myos) {
        myos.os << myos.data << myos.separator;
        return;
    }
};


int main()
{	const int SIZE = 5;
    int a[SIZE] = {5,21,14,2,3};
    double b[SIZE] = { 1.4, 5.56,3.2,98.3,3.3};
    list<int> lst(a,a+SIZE);
    myostream_iteraotr<int> output(cout,",");
    Copy( lst.begin(),lst.end(),output);
    cout << endl;
    myostream_iteraotr<double> output2(cout,"--");
    Copy(b,b+SIZE,output2);
    return 0;
}