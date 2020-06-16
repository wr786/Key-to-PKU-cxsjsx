#include <iostream>
#include <algorithm>
using namespace std;
long long a[1000001]; // y不重要，压缩成1维
long long presum[1000001];    // 前缀和，但要注意防溢出！qwq
int n, m;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m;
    while(m--) {
        int l, t, w, h; cin >> l >> t >> w >> h;
        for(int i=l+1; i<=l+w; i++)
            a[i] += h;  // 注意用h，而不是++！
    }
    for(int i=1; i<=n; i++)
        presum[i] = presum[i-1] + a[i];
    int ans = 0;
    long long mindif = 0x3f3f3f3f;
    for(int i=0; i<=n; i++) {
        long long lhs = i?presum[i]:0;
        long long rhs = presum[n] - presum[i];
//        cout << i << ":" << lhs << " " << rhs << endl;
        if(lhs >= rhs && lhs - rhs <= mindif) {
            ans = i;
            mindif = lhs - rhs;
        }
    }
    cout << ans << endl;
    return 0;
}