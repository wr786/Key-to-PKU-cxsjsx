#include <iostream>
using namespace std;

inline int gcd(int a, int b) {return b? gcd(b, a%b): a;}

int a[601];

int main() {
    int n, ans = 0;
    cin >> n;
    for(int i=0; i<n; i++) {
        cin >> a[i];
    }
    for(int i=0; i<n-1; i++)
        for(int j=i+1; j<n; j++) {
            if(gcd(a[i], a[j]) == 1) 
                ans++;
        }
    cout << ans << endl;
    return 0;
}