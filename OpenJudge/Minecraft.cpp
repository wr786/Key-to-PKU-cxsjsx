#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio((false)); cin.tie(0);
    int n; cin >> n;
    int ans = 0x3f3f3f3f;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=i; j++) {
            if(n % (i*j) == 0) {
                int k = n / i / j;
                ans = min(ans, 2*(i*j+i*k+j*k));
            }
        }
    cout << ans << endl;
}