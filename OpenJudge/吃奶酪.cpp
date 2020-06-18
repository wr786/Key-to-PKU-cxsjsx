#include <iostream>
#include <algorithm>
#include <cstring>
#include <limits>
using namespace std;
int n;
int a[100001];
long long dp[100001][2];    // 防爆

int main() {
    int t; cin >> t;
    while(t--) {
        cin >> n;
        for(int i=1; i<=n; i++)
            cin >> a[i];
        for(int i=1; i<=n; i++) {
            dp[i][0] = dp[i][1] = 0;
        }
        dp[1][1] = a[1];
        for(int i=2; i<=n; i++) {
            dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
            dp[i][1] = max(dp[i][1], dp[i-1][0] + a[i]);
        }
        cout << max(dp[n][0], dp[n][1]) << endl;
    }
}