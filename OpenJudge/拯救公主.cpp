#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>

using namespace std;
#define endl '\n'
int n, m, v;
int ans = -1;
int a[101][101];
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int vis[101][101][11][4];   // x,y,power,dir

struct Node {
    int posx;
    int posy;
    int power;
    int dir;    // direction
    int costTime;

    bool operator<(const Node &other) const {
        return costTime > other.costTime;
    }
};

priority_queue<Node> pq;

enum FLAGS {
    JUMP = 37510,
    PRINCESS = 786,
    TRAP = -1,
    BLANK = 0,
};

//inline bool prune(const Node &node) {
//    return vis[node.posx][node.posy][node.power][node.dir] <= node.costTime;   // mem
//}   // 返回true代表要剪

inline bool check_boundary(int x, int y) {
    return !(x < 1 || y < 1 || x > n || y > m);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 0;
    while (cin >> n >> m >> v, n || m || v) {
        t++;
        int startx = 0, starty = 0;
        ans = -1;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                char tmp;
                cin >> tmp;
                if (tmp == 'T') {
                    a[i][j] = PRINCESS;
                } else if (tmp == '#') {
                    a[i][j] = TRAP;
                } else if (tmp == '.') {
                    a[i][j] = BLANK;
                } else if (tmp == 'E') {
                    a[i][j] = JUMP;
                } else if (tmp == 'S') {
                    a[i][j] = BLANK;
                    startx = i;
                    starty = j;
                }
            }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                for (int p = 0; p <= v; p++)
                    for (int d = 0; d < 4; d++)
                        vis[i][j][p][d] = 0x3f3f3f3f;
        while (!pq.empty()) pq.pop();
        pq.push(Node{startx, starty, v, 0, 0});
        while (!pq.empty()) {
            // BFS
            Node cur = pq.top();
            pq.pop();
            int &x = cur.posx;
            int &y = cur.posy;
            if (a[x][y] == PRINCESS) {
                ans = cur.costTime;
                break;
            }
//            if (prune(cur)) continue;
//            vis[x][y][cur.power][cur.dir] = min(vis[x][y][cur.power][cur.dir], cur.costTime);
            if (a[x][y] == TRAP) continue;
            if (a[x][y] == JUMP) {
                // 特殊判断是否要跳跃
                // 显然S和E不会是同一格，所以必然有上次的方向dir
                bool flag = true;
                for (int p = 1; p <= cur.power && flag; p++) {
                    int nx = x + dx[cur.dir] * p, ny = y + dy[cur.dir] * p;
//                    if (!check_boundary(nx, ny)) continue;    // 被墙挡了只是掉下来，所以不用判断边界
                    if (!check_boundary(nx, ny)) flag = false;
                    nx = max(1, nx);
                    ny = max(1, ny);
                    nx = min(n, nx);
                    ny = min(m, ny);
                    if (a[nx][ny] == TRAP) continue;
//                    vis[nx][ny][p][cur.dir] = min(vis[nx][ny][p][cur.dir], cur.costTime);
                    if(vis[nx][ny][p][cur.dir] > cur.costTime) {
                        vis[nx][ny][p][cur.dir] = cur.costTime;
                        pq.push(Node{nx, ny, flag ? p : cur.power, cur.dir, cur.costTime});
                    }
                }
            }
            for (int dir = 0; dir < 4; dir++) {
                int nx = x + dx[dir], ny = y + dy[dir];
                if (!check_boundary(nx, ny)) continue;
                if (a[nx][ny] == TRAP) continue;
//                vis[nx][ny][cur.power][dir] = min(vis[nx][ny][cur.power][dir], cur.costTime+1);
                if(vis[nx][ny][cur.power][dir] > cur.costTime+1) {
                    vis[nx][ny][cur.power][dir] = cur.costTime + 1;
                    pq.push(Node{nx, ny, cur.power, dir, cur.costTime + 1});
                }
            }
        }
        cout << "Case #" << t << ": " << ans << endl;
    }
    return 0;
}