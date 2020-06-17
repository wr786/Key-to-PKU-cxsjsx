#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int n, m;
char a[501][501];
int flag[501][501];

inline bool check_boundary(int x, int y) {
    return (x >= 1 && y >= 1 && x <= n && y <= m);
}

void dfs(int x, int y) {
    flag[x][y] = 1;
    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (check_boundary(nx, ny) && a[nx][ny] == 'O' && !flag[nx][ny])    // flag充当vis
            dfs(nx, ny);
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        memset(flag, 0, sizeof(flag));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                cin >> a[i][j];
        for (int i = 1; i <= m; i++) {
            if (a[1][i] == 'O') dfs(1, i);
            if (a[n][i] == 'O') dfs(n, i);
        }
        for (int i = 1; i <= n; i++) {
            if (a[i][1] == 'O') dfs(i, 1);
            if (a[i][m] == 'O') dfs(i, m);
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (a[i][j] == 'X') cout << a[i][j];
                else {
                    if (flag[i][j]) cout << a[i][j];
                    else cout << 'X';
                }
            }
            cout << '\n';
        }
        if (T) cout << '\n'; // 空行
    }
    return 0;
}