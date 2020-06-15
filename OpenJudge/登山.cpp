#include <iostream>
#include <algorithm>

using namespace std;
#define endl '\n'
int n;
int a[1001];
int dp1[1001], dp2[1001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        dp1[i] = dp2[i] = 1;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j < i; j++)
            if (a[j] < a[i])
                dp1[i] = max(dp1[i], dp1[j] + 1);
    for (int i = n; i >= 1; i--)
        for (int j = n; j > i; j--)
            if (a[j] < a[i])
                dp2[i] = max(dp2[i], dp2[j] + 1);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int l = i; l; l--)
            for (int r = i; r <= n; r++) {
                ans = max(ans, dp1[l] + dp2[r] + (l == r ? -1 : 0));
            }
    }
    cout << ans << endl;
}