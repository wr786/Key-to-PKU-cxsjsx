#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;
int n, m, k;
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int a[101][101];
bool vis[101][101][11];  // 第三维是t%k
enum BLOCK {
    STONE = -1,
    EXIT,
    EMPTY,
};

struct Node {
    pair<int, int> pos;
    int costTime;

    bool operator<(const Node &other) const {
        return costTime > other.costTime;
    }

    Node(int x = 0, int y = 0, int t = 0) : pos({x, y}), costTime(t) {}
};

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m >> k;
        priority_queue<Node> pq;
        while (!pq.empty()) pq.pop();
        memset(vis, false, sizeof(vis));
        int sx, sy;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                char tmp;
                cin >> tmp;
                if (tmp == '.') a[i][j] = EMPTY;
                if (tmp == '#') a[i][j] = STONE;
                if (tmp == 'E') a[i][j] = EXIT;
                if (tmp == 'S') {
                    a[i][j] = EMPTY;
                    sx = i;
                    sy = j;
                }
            }
        pq.push(Node(sx, sy, 0));
        vis[sx][sy][0] = true;
        int ans = -1;
        while (!pq.empty()) {
            Node cur = pq.top();
            pq.pop();
            int &x = cur.pos.first, &y = cur.pos.second;
            if (a[x][y] == EXIT) {
                ans = cur.costTime;
                break;
            }
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx < 1 || ny < 1 || nx > n || ny > m) continue;
                if (a[nx][ny] == STONE && (cur.costTime + 1) % k != 0) continue;
                if (!vis[nx][ny][(cur.costTime + 1) % k]) {
                    vis[nx][ny][(cur.costTime + 1) % k] = true;
                    pq.push(Node(nx, ny, cur.costTime + 1));
//                    cout << "(" << nx << ", " << ny << "):" << cur.costTime+1<<"\n";
                }
            }
        }
        cout << (ans == -1 ? "Oop!" : to_string(ans)) << endl;
    }
}