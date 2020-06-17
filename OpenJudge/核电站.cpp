#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m;
long long dp[60][2];  // 仍然是代表放与不放

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    dp[0][0] = 1;   // 初始状态
    for (int i = 1; i <= n; i++) {
        dp[i][0] = dp[i - 1][0] + dp[i - 1][1];
        for (int j = 1; j < min(m, i + 1); j++) {  // 防越界
            for (int k = 0; k <= 1; k++)
                dp[i][1] += dp[i - j][k];
            dp[i][1] -= dp[i - j][1]; // 去掉连着M个都这样的情况
        }
    }
    cout << dp[n][1] + dp[n][0] << endl;
    return 0;
}