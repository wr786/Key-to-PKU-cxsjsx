#include <iostream>
#include <algorithm>

using namespace std;
#define LIM (1<<20)
int n, t, ans;
int num[21];
int dp[LIM];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> t;
    for (int i = 0; i < n; i++) {
        cin >> num[i];
        dp[(1 << i)] = num[i];
    }
    for (int cmb = 0; cmb < (1 << n); cmb++) {
        for (int i = 0; i < n; i++) {
            if (cmb & (1 << i)) {
                dp[cmb] = dp[(1 << i)] + dp[cmb ^ (1 << i)];
                break;
            }
        }
        if (dp[cmb] == t) ans++;
    }
    cout << ans << endl;
    return 0;
}