// luogu NOI-，可还行嗷
#include <iostream>
#include <algorithm>
using namespace std;
int n;
int a[201];
int afterBlocks[201];
int dp[201][201][201];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    for(int t=1; t<=T; t++) {
        cin >> n;
        for(int i=1; i<=n; i++)
            cin >> a[i];
        for(int i=n; i; i--) {
            for(int j=i; j<=n; j++) {
                if(a[j] == a[i])
                    afterBlocks[i]++;
            }
        }
        for(int i=n; i; i--)
            for(int j=i; j<=n; j++) {
                for(int k=0; k<=afterBlocks[j]; k++) {
                    dp[i][j][k] = dp[i][j-1][0] + (k+1) * (k+1);
                }
                for(int p=i; p<j; p++) {
                    if(a[p] == a[j]) {
                        for(int k=0; k<=afterBlocks[j]; k++)
                            dp[i][j][k] = max(dp[i][j][k], dp[i][p][k+1] + dp[p+1][j-1][0]);
                    }
                }
            }
        cout << "Case " << t << ": " << dp[1][n][0] << endl;
    }
}