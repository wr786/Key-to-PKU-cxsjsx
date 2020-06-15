#include <iostream>
#include <algorithm>
using namespace std;
int n, ans;
int a[1001];
int dp[1001];    // 到_为止，最大数是a[_]的最大……和

int main() {
    cin >> n;
    for(int i=1; i<=n; i++)
        cin >> a[i];
    for(int i=1; i<=n; i++) {
        dp[i] = max(dp[i], a[i]);
        for(int j=1; j<i; j++) {
            if(a[j] < a[i]) {
                dp[i] = max(dp[i], dp[j] + a[i]);
            }
        }
        ans = max(ans, dp[i]);
    }
    cout << ans << endl;
    return 0;
}