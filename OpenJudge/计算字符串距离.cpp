#include <iostream>
#include <string>
using namespace std;
int dp[1001][1001];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        string a, b; cin >> a >> b;
        int la = a.length(), lb = b.length();
        for(int i=1; i<=la; i++) dp[i][0] = i;
        for(int j=1; j<=lb; j++) dp[0][j] = j;
        for(int i=1; i<=la; i++)
            for(int j=1; j<=lb; j++) {
                if(a[i-1] == b[j-1]) {
                    // a的第i个和b的第j个相等
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = min(min(dp[i-1][j], dp[i][j-1]), dp[i-1][j-1]) + 1;
                }
            }
        cout << dp[la][lb] << endl;
    }
}