#include <iostream>
#include <algorithm>
using namespace std;
int n, m;
int dp[101][2]; // 0代表本月在北京，1代表在南京
int a[101], b[101];

int main() {
    cin >> n >> m;
    for(int i=1; i<=n; i++)
        cin >> a[i] >> b[i];
    dp[1][0] = a[1], dp[1][1] = b[1];
    for(int i=2; i<=n; i++) {
        dp[i][0] = max(dp[i-1][0], dp[i-1][1]-m) + a[i];
        dp[i][1] = max(dp[i-1][1], dp[i-1][0]-m) + b[i];
    }
    cout << max(dp[n][0], dp[n][1]) << endl;
    return 0;
}