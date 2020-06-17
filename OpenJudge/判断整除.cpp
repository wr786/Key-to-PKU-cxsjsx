#include <iostream>
#include <algorithm>
using namespace std;
int n, k;
int a[10001];
bool dp[10001][101];    // 同余 mod k

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k;
    for(int i=1; i<=n; i++)
        cin >> a[i];
    dp[0][0] = true;
    for(int i=1; i<=n; i++) {
        for(int j=0; j<k; j++ ) {
            dp[i][j] = dp[i-1][(j+a[i])%k]  // 这里选择加法
                    || dp[i-1][(j+k-a[i]%k)%k]; // 这里选择除法
        }
    }
    cout << (dp[n][0]?"YES":"NO") << endl;
    return 0;
}