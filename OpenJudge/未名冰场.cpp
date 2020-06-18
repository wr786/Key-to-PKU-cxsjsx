// 染色裸题
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
int n, m;
char a[101][101];
int vis[101][101];
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1}, dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int idx;

void dfs(int x, int y, int color) {
    vis[x][y] = color;
    for (int d = 0; d < 8; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx < 1 || ny < 1 || nx > n || ny > m) continue;
        if (vis[nx][ny] || a[nx][ny] == '*') continue;
        dfs(nx, ny, color);
    }
}

int main() {
    while (cin >> n >> m, n||m) {
        memset(vis, 0, sizeof(vis));
        idx = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                cin >> a[i][j];
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                if (a[i][j] == '@' && !vis[i][j]) {
                    dfs(i, j, ++idx);
                }
            }
        cout << idx << endl;
    }
}