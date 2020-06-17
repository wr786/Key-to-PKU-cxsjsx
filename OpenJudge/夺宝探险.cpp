#include <iostream>
#include <algorithm>

using namespace std;
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int a[21][21];
bool vis[21][21], visjew[101];
int m, n, k;
int ans;

inline bool check_boundary(int x, int y) {
    return (x >= 1 && y >= 1 && x <= m && y <= n);
}

void dfs(int x, int y, int cnt) {
    ans = max(ans, cnt);
    for(int d=0; d<4; d++) {
        int nx = x+dx[d], ny = y +dy[d];
        if(!check_boundary(nx, ny)) continue;
        if(vis[nx][ny] || visjew[a[nx][ny]]) continue;
        vis[ny][ny] = true;
        visjew[a[nx][ny]] = true;
        dfs(nx, ny, cnt + 1);   // 如果能走，那必然是新的宝藏
        vis[ny][ny] = false;
        visjew[a[nx][ny]] = false;
    }
}

int main() {
    cin >> m >> n >> k;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j];
    vis[1][1] = true;
    visjew[a[1][1]] = true;
    dfs(1, 1, 1);
    cout << ans << endl;
    return 0;
}