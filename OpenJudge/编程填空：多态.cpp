#include <iostream>
using namespace std;

class Base {
public:
   virtual Base& fun() { cout << "base fun" << endl; return *this; }
   virtual Base& foo() { cout << "base foo" << endl; return *this; }
};

class Derived: public Base {
public:
   Base& fun() { cout << "derived fun" << endl; return *this; }
   Base& foo() { cout << "derived foo" << endl; return *this; }
};

Base& foo();
Base& fun();
// 在此处补充你的代码
Base& foo() {Derived* pd = new Derived(); pd->foo(); return *pd;}
Base& fun() {Base* pb = new Base(); pb->fun(); return *pb;}
int main() {
   foo().fun().foo();
   fun().foo().fun();
   return 0;
}