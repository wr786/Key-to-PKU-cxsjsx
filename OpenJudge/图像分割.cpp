// 老染色了
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int n, m, k;
int a[51][51];
int vis[51][51];
int idx;
//int dx[8] = {0,1,1,1,0,-1,-1,-1}, dy[8] = {1,1,0,-1,-1,-1,0,1};
int dx[4] = {0,1,0,-1}, dy[4]={1,0,-1,0};   // 倒是说清楚相邻啊

void dfs(int x, int y, int color) {
    vis[x][y] = color;
    for(int d=0; d<4; d++) {
        int nx=  x + dx[d], ny = y + dy[d];
        if(nx < 1 || ny < 1 || nx> n || ny > m) continue;
        if(abs(a[nx][ny] - a[x][y]) > k) continue;
        if(!vis[nx][ny]) dfs(nx, ny, color);
    }
}

int main() {
    while(cin >> n >> m >> k, n||m||k) {
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
                cin >> a[i][j];
        idx = 0;
        memset(vis, 0, sizeof(vis));
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
                if(!vis[i][j])
                    dfs(i, j, ++idx);
        cout << idx << endl;
    }
}