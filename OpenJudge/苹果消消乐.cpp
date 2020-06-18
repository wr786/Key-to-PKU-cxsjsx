#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int n, m;
int a[101];
int b[101];
int ans;

void dfs(int pos, int chance, int last) {   // 必然是选择连续的那几个
    if(pos == n+1) {
        int last = 0;
        for(int i=1; i<=n; i++) {
            if(a[b[i]]) {
                ans = max(ans, b[i] - 1 - last);
                last = b[i];
            }
        }
        ans = max(ans, 100 - last);
        return;
    }
    if(chance == 0) {   // 提前结束
        dfs(n+1, chance, 0);
        return;
    }
    a[b[pos]] = 0;
    dfs(pos+1, chance-1, 1);
    if(!last) {
        a[b[pos]] = 1;
        dfs(pos+1,chance, 0);
    }
}

int main() {
    int t; cin >> t;
    while(t--) {
        ans = 0;
        cin >> n >> m;
        memset(a, 0, sizeof(a));
        for(int i=1; i<=n; i++) {
            cin >> b[i];
            a[b[i]] = 1;
        }
        if(m >= n) cout << 100 << endl;
        else {
            dfs(1, m, 0);
            cout << ans << endl;
        }
    }
}