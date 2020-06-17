#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>=
using namespace std;
int n;
int a[100001];
int dp[100001][2];  // 0表示今晚不下手

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        memset(dp, 0, sizeof(dp));
        for(int i=1; i<=n; i++) {
            dp[i][1] = a[i];    // 初始状态
        }
        for(int i=1; i<=n; i++) {
            dp[i][0] = max(dp[i-1][0], dp[i-1][1]); // 无论上次动不动手，这次都可以不动手
            dp[i][1] = max(dp[i][1], dp[i-1][0] + a[i]);
        }
        cout << max(dp[n][0], dp[n][1]) << endl;
    }
    return 0;
}