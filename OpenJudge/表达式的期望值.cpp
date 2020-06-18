// & | ^ ，暗示位运算很行（
#include <iostream>
#include <iomanip>
using namespace std;
int A[210];
char O[210];
double P[210];
int T, n;

inline double f(double exp, char op, bool rhs) {
    if(op == '&') return rhs? exp: 0.;
    else if(op == '|') return rhs? 1.: exp;
    else if(op == '^') return rhs? 1.-exp: exp; // 注意这里
    else return 0;
}

int main() {
    while(cin >> n) {
        ++T;
        for(int i=0; i<=n; i++) cin >> A[i];
        for(int i=1; i<=n; i++) cin >> O[i];
        for(int i=1; i<=n; i++) cin >> P[i];
        double ans = 0.;
        for(int i=0; i<=20; i++) {
            // 小于2^20
            double tmp = 0. + ((A[0]>>i) & 1);
            for(int k=1; k<=n; k++) {
                tmp = tmp * P[k] + f(tmp, O[k], ((A[k]>>i)&1)) * (1.-P[k]);
            }
            ans += (1<<i) * tmp;
        }
        cout << "Case " << T << ": \n";
        cout << fixed << setprecision(6) << ans << endl;
    }
}