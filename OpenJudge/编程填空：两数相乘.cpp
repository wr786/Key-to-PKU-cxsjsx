#include <iostream>
using namespace std;
class Number {
public:
    int num;
    Number(int n): num(n) {}
// 在此处补充你的代码
    Number operator * (const Number & other) {
        return num * other.num;
    }
    friend bool operator == (int n, const Number & other) {
        return n == other.num;
    }
    friend ostream& operator << (ostream& os, const Number& other) {
        os << other.num;
        return os;
    }
};
int main() {
    int t;
    int m,n;
    cin >> t;
    while(t--) {
        cin >> m>> n;
        Number n1(m), n2 = n1 * n;
        if( m * n == n2 )
            cout << n2 << endl;
    }
    return 0;
}