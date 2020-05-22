#include <iostream>
#include <algorithm>
using namespace std;

long long dp[1000][1000]; // 和，最小数

int main() {
    dp[1][1] = 1;
    dp[2][1] = 2; dp[2][2] = 1;
    for(int i=3; i<=250; i++) {
        dp[i][i] += 1; // 单独
        if(i % 2 == 0) dp[i][i/2] += 1; // 分割
        for(int j=i-1; j>=1; j--) {
            dp[i][j] += dp[i][j+1];
            if(i > 2*j) {
                dp[i][j] += dp[i-2*j][j];
            }
        }
    }
    int x;
    while(cin >> x) {
        if(!x) break;
        cout << x << " " << dp[x][1] << endl;
    }
    return 0;
}