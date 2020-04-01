#include <iostream>
using namespace std;
// 在此处补充你的代码
template<typename T1, typename T2>
class f {
private:
    T1 x;
public:
    f(T1 _x): x(_x) {}
    auto operator () (T2 y) -> decltype(x + y) {
        return y + x;
    }
};
////////////////////
int main()
{
    cout << f<int,int>(7)(9) << endl;   //16
    cout << f<string,string> (" hello!")("world")  <<endl; // world hello!
    cout << f<char,string> ('!')("world") << endl;


    return 0;    //world!
}