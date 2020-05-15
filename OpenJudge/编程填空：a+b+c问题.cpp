// by Drizzle

#include <iostream>
using namespace std;
// 在此处补充你的代码
class A {
protected:
 int dat;
public:
 A(int d) :dat(d) {}
 int get_value() {
  return dat;
 }
 operator int() { return dat; }
 A operator+(A* o)
 {
  return A(dat + o->dat);
 }
 A* operator->() { return this; }
};
class B :public A {
public:
 B(int d) : A(d) {}
};
class C :public A {
public:
 C(int d) : A(d) {}
};
////////////////////
int main() {
    int t;
    cin >> t;
    while (t --){
        int aa, bb, cc;
        cin >> aa >> bb >> cc;
        A a(aa);
        B b(bb);
        C c(cc);
        A* x = &a;
        A* y = &b;
        A* z = &c;
        cout << (x->get_value() + y->get_value() + z->get_value()) << " ";
        cout << ((*x) + y + z)->get_value() << endl;
    }
    return 0;
}