#include <iostream>
#include <algorithm>

using namespace std;
int n;
int a[1001];
int dp[1001][2];   // 以j为结尾，是否使用过权限

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    dp[1][0] = 1;
    dp[1][1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i][0] = dp[i][1] = 1;
        for (int j = 1; j < i; j++) {
            if (a[j] >= a[i])
                dp[i][0] = max(dp[i][0], dp[j][0] + 1),
                        dp[i][1] = max(dp[i][1], dp[j][1] + 1),
                        dp[i][1] = max(dp[i][1], dp[j][0] + 1);
            else
                dp[i][1] = max(dp[i][1], dp[j][0] + 1);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, max(dp[i][0], dp[i][1]));
    cout << ans << endl;
    return 0;
}