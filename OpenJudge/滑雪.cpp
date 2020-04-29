#include <iostream>
using namespace std;
#define endl '\n'
int a[101][101];
int vis[101][101];
int m, n;
int ans;
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

void search(int x, int y) {
    vis[x][y] = max(vis[x][y], 1);
    for(int dir=0; dir<4; dir++) {
        int nx = x+dx[dir], ny = y+dy[dir];
        if(nx>=1 && ny >=1 && nx<=m && ny<=n && a[nx][ny] < a[x][y]) {
            if(!vis[nx][ny])
                search(nx, ny);
            vis[x][y] = max(vis[x][y], vis[nx][ny]+1);
        }
    }
    ans = max(ans, vis[x][y]);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> m >> n;
    for(int i=1; i<=m; i++)
        for(int j=1; j<=n; j++){
            cin >> a[i][j];
        }
    for(int i=1; i<=m; i++)
        for(int j=1; j<=n; j++)
            search(i, j);
    cout << ans << endl;
    return 0;
}