#include<iostream>
using namespace std;
int a[10][10];
int dx[4] = {0,1,0,-1}, dy[4] = {1,0,-1,0};
bool vis[10][10];
int ans[30];
int tmp[30];
int minLength = 0x3f3f3f3f;

void dfs(int x, int y, int depth) {
    if(depth > minLength) return;   // prune
    tmp[depth] = x*10 + y;
    if(x == 5 && y == 5) {  // target
        if(depth < minLength) {
            for(int i=1; i<=depth; i++) {
                ans[i] = tmp[i];
            }
            minLength = depth;
        }
        return;
    }
    for(int dir=0; dir<4; dir++) {
        int nx = x + dx[dir], ny = y + dy[dir];
        if(!nx || !ny || nx>5 || ny>5 || vis[nx][ny] || a[nx][ny]) continue;
        vis[nx][ny] = true;
        dfs(nx, ny, depth+1);
        vis[nx][ny] = false;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    for(int i=1; i<=5; i++)
        for(int j=1; j<=5; j++)
            cin >> a[i][j];
    dfs(1,1,1);
    for(int i=1; ans[i]; i++) {
        cout << "(" << ans[i]/10-1 << ", " << ans[i]%10-1 << ")\n";
    }
    return 0;
}