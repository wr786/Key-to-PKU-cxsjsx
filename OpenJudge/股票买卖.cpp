#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int n;
int a[100001];  // 草，居然不是50，看错力（大悲
int dp[3][2];
// 滚动窗口，省一维
// _, _ => buytimes, if with stock

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        cin >> n;
        for(int i=1; i<=n; i++) {
            cin >> a[i];
            a[i] += 1000000; // 处理负数，不想出现负数，绝对值不会超过这个数，反正结果是相对数字
        }
        if(n == 1) {    // 特判，有点坑（
            cout << 0 << endl;
            continue;
        }
        // init
        dp[0][0] = 0, dp[1][0] = -0x3f3f3f3f, dp[2][0] = -0x3f3f3f3f;
        dp[0][1] = -0x3f3f3f3f, dp[1][1] = -a[1], dp[2][1] = -0x3f3f3f3f;
        for(int i=2; i<=n; i++) {
            for(int buytimes=0; buytimes<=2; buytimes++) {
                dp[buytimes][0] = max(dp[buytimes][0], dp[buytimes][1] + a[i]);
                if(buytimes) dp[buytimes][1] = max(dp[buytimes][1], dp[buytimes-1][0] - a[i]);
            }
        }
        cout << max(dp[2][0], max(dp[1][0], dp[0][0])) << endl; // 同天买卖就相当于没有买卖
    }
}