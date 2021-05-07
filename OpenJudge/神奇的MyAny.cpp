#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
using namespace std;
class MyClass {	
public:
  int n;
  MyClass(int m):n(m) { }
	void f() { cout << n << " func." << endl; }
};
// 在此处补充你的代码
class MyAny {
public:
    /*  因为MyAny是没有类型的
        但是显然，我们的MyAny需要类型
        我们就在内部创建一个带模板的派生类
    */
    class Base {
    public:
        Base() {}
        virtual ~Base() {}
        virtual Base* get_data() = 0;
    };
    template<class T>
    class Derived:public Base {
    public:
        T data;
        Derived(const T data): data(data) {}
        ~Derived() {}
        Base* get_data() {
            return new Derived<T>(data);
        }
    };

    Base* pdata;
    MyAny() {pdata = nullptr;}
    template<class T>
    MyAny(const T data) {
        pdata = new Derived<T>(data);
    }
    MyAny(const MyAny& other) {
        pdata = (other.pdata)->get_data();
    }
    ~MyAny() {
        if(pdata != nullptr) {
            delete pdata;
        }
    }
    MyAny& operator= (const MyAny& other) {
        if(pdata != nullptr) {
            delete pdata;
        }
        pdata = (other.pdata)->get_data();
        return (*this);
    }
};

template<class T>
T MyAny_cast(const MyAny& o) {
    return ((MyAny::Derived<T>*)(o.pdata))->data;
}

template<class T>
T* MyAny_cast(const MyAny* p) {
    if(typeid(*(p->pdata->get_data())) != typeid(MyAny::Derived<T>)) {
        return NULL;
    } else {
        return &(((MyAny::Derived<T>*)(p->pdata))->data);
    }
}

// 在此处结束你的代码
int main() 
{
	while(true) {
		int n;
		string s;
		cin >>  n >> s;
		if ( n == 0)
			break;
		MyAny a = n;
	 	cout << MyAny_cast<int>(a) << endl;
		a = s;
		cout << MyAny_cast<string>(a) << endl;
		a = MyClass(n+1);
		MyAny b = n + 2;
		MyAny * p = new MyAny(MyClass(n+3));
		MyAny c = MyClass(n+4);
	 	c = * p;
	  	b = * p;
		delete p;
		MyAny d = b;
		MyAny_cast<MyClass>(&a)->f();
		MyAny_cast<MyClass>(&b)->f();	
		MyAny_cast<MyClass>(&c)->f();	
		MyAny_cast<MyClass>(&d)->f();		
		c = s + "OK";
		cout << MyAny_cast<string>(c) << endl;	
		int * pi = MyAny_cast<int> ( & c);
		if( pi == NULL)
			cout << "not a int" << endl;
		else
			cout << "the int is " << * pi << endl;
		string * ps = MyAny_cast<string> ( & c);
		if( ps == NULL)
			cout << "not a string" << endl;
		else
			cout << "the string is " << * ps << endl;
	}
}