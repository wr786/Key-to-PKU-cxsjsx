#include <iostream>
#include <algorithm>
using namespace std;

int n, m;
int w[3405], v[3405];
int dp[13000];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    for(int i=1; i<=n; i++) cin >> w[i] >> v[i];
    for(int i=1; i<=n; i++)
        for(int j=m; j>=w[i]; j--) {
            dp[j] = max(dp[j], dp[j-w[i]] + v[i]);
        }
    int ans = 0;
    for(int i=0; i<=m; i++) ans = max(ans, dp[i]);  // 未必填满了
    cout << ans << endl;
}