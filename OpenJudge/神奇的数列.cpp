// 有点眼熟，老区间DP了
#include <iostream>
#include <algorithm>
#include <cstring>
#include <limits>
using namespace std;
const int INF = 0x3f3f3f3f;
int n;
int a[201];
int blockAfter[201];    // 后面有几个与a[i]相同的
int dp[201][201][201];  // 考虑i~j这个区间，同时j后面有k个相同的元素

int main() {
    int T; cin >> T;
    for(int t=1; t<=T; t++) {
        cout << "Case " << t << ": ";
        cin >> n;
        memset(blockAfter, 0, sizeof(blockAfter));
        for(int i=1; i<=n; i++)
            cin >> a[i];
        for(int i=1; i<=n; i++) {
            for(int j=i+1; j<=n; j++)
                if(a[i] == a[j])
                    blockAfter[i]++;
            for(int j=1; j<=n; j++)
                for(int k=0; k<=blockAfter[j]; k++)
                    dp[i][j][k] = INF;
        }
        for(int i=n; i; i--) {
            // 倒序，不然没法算第三维
            dp[i][i-1][0] = 0;  // 初始化
            for(int j=i; j<=n; j++) {
                for(int k=0; k<=blockAfter[j]; k++) {
                    dp[i][j][k] = dp[i][j-1][0] + 1;  // 清除j以及后面k块
                }
                for(int l=i; l<j; l++) {
                    if(a[l] == a[j]) {
                        for(int k=0; k<=blockAfter[j]; k++)
                            dp[i][j][k] = min(dp[i][j][k], dp[i][l][k+1] + dp[l+1][j-1][0]);
                    }
                }
            }
        }
        cout << dp[1][n][0] << endl;
    }
}