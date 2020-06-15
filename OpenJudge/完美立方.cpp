#include <iostream>
using namespace std;

inline int pow3(int x) {return x*x*x;}

int main() {
    int n;
    cin >> n;
    for(int a=2; a<=n; a++) {
        int target = pow3(a);
        for(int b=2; b<a; b++) {
            for(int c=b; c<a; c++) {
                for(int d=c; d<a; d++) {
                    if(target == pow3(d) + pow3(b) + pow3(c)) {
                        cout << "Cube = " << a << ", Triple = (" << b << "," << c << "," << d << ")\n";
                    }
                }
            }
        }
    }
    return 0;
}