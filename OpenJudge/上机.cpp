#include <iostream>
#include <algorithm>
using namespace std;
#define LIM 10001
int n;
int a[LIM], b[LIM], c[LIM];
int dp[LIM][4]; // 1~i 上 i的状态为j
enum STATUS {
    EMPTY,
    LEFT,
    RIGHT,
    BOTH,
};

int main() {
    cin >> n;
    for(int i=1; i<=n; i++)
        cin >> a[i];
    for(int i=1; i<=n; i++)
        cin >> b[i];
    for(int i=1; i<=n; i++)
        cin >> c[i];
    dp[1][EMPTY] = a[1]; dp[1][RIGHT] = b[1];
    dp[1][LEFT] = dp[1][BOTH] = -0x3f3f3f3f;    // 不可能
    for(int i=2; i<=n; i++) {
        dp[i][EMPTY] = max(dp[i-1][RIGHT], dp[i-1][BOTH]) + a[i];
        dp[i][LEFT] = max(dp[i-1][LEFT], dp[i-1][EMPTY]) + b[i];
        dp[i][RIGHT] = max(dp[i-1][RIGHT], dp[i-1][BOTH]) + b[i];
        dp[i][BOTH] = max(dp[i-1][LEFT], dp[i-1][EMPTY]) + c[i];
    }
    cout << max(dp[n][EMPTY], dp[n][LEFT]) << endl;
    return 0;
}