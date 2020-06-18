#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;
int n, w;
int cost[19];
int bag[19];
int ans = numeric_limits<int>::max();

void dfs(int cur, int cnt) {
    if(cnt >= ans) return;  // prune
    if(cur == 0) {
        // 装完了
        ans = min(ans, cnt);
        return;
    }
    for(int i=1; i<=cnt; i++) {
        if(bag[i] >= cost[cur]) {   // 用旧的包来装
            bag[i] -= cost[cur];
            dfs(cur-1, cnt);
            bag[i] += cost[cur];
        }
    }
    if(bag[cnt+1] >= cost[cur]) {   // 用新的包来装
        bag[cnt+1] -= cost[cur];
        dfs(cur-1, cnt+1);
        bag[cnt+1] += cost[cur];
    }
}

int main() {
    cin >> n >> w;
    for (int i = 1; i <= n; i++) {
        cin >> cost[i];
        bag[i] = w;
    }
    sort(cost + 1, cost + 1 + n);
    dfs(n, 1);
    cout << ans << endl;
    return 0;
}