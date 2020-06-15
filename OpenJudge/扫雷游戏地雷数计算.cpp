#include <iostream>

using namespace std;
int n, m;
int dx[8] = {1, 0, -1, 0, 1, -1, 1, -1}, dy[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int a[101][101];

inline int cnt(int x, int y) {
    int ret = 0;
    for (int dir = 0; dir < 8; dir++) {
        int nx = x + dx[dir], ny = y + dy[dir];
        if (a[nx][ny] == -1) ret++;
    }
    return ret;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            if (c == '*') a[i][j] = -1;
            else a[i][j] = 0;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == -1) cout << "*";
            else {
                cout << cnt(i, j);
            }
        }
        cout << endl;
    }
    return 0;
}