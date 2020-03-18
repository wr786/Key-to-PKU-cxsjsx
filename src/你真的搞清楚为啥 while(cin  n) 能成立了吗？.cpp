#include <iostream>
using namespace std;
class MyCin
{
// 在此处补充你的代码
private:
    bool canReadIn;
public:
    MyCin(): canReadIn(true) {}
    template<class T>
    MyCin& operator >> (T& num) {
        cin >> num;
        if(num == -1) canReadIn = false;
        return *this;
    }
    operator bool() {return canReadIn;} // 重载类型转换符
};
int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2)
        cout  << n1 << " " << n2 << endl;
    return 0;
}