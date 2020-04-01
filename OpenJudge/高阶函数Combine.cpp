#include <iostream>
using namespace std;
// 在此处补充你的代码
template <typename F1, typename F2, typename T>
class combine {
private:
    F1 f1;
    F2 f2;
public:
    combine(F1 _f1, F2 _f2): f1(_f1), f2(_f2) {}
    auto operator () (T x) -> decltype(f1(f1(x) + f2(x))) {
        return f1(f1(x) + f2(x));
    }
};
////////////////////
int main()
{
    auto Square = [] (double a) { return a * a; };
    auto Inc = [] (double a) { return a + 1; };
    cout << combine<decltype(Square),decltype(Inc),int>(Square,Inc)(3) << endl;
    cout << combine<decltype(Inc),decltype(Square),double>(Inc,Square)(2.5) << endl;

    return 0;
}