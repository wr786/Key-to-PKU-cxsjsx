// 最长下降子序列&&最长上升子序列
#include <iostream>
#include <algorithm>
using namespace std;
#define endl '\n'
int n;
int a[101], dp[101], dp2[101];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int _t; cin >> _t;
    while(_t--) {
        int ans = 0;
        cin >> n;
        for(int i=1; i<=n; i++) {
            cin >> a[i];
            dp[i] = dp2[i] = 1;
        }
        for(int i=1; i<=n; i++) {
            for(int j=1; j<i; j++) {
                if(a[j] > a[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
                if(a[j] < a[i]) {
                    dp2[i] = max(dp2[i], dp2[j] + 1);
                }
            }
            ans = max(ans, dp[i]);
            ans = max(ans, dp2[i]);
        }

        cout << ans << endl;
    }
}