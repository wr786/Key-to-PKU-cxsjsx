#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;
int n, m, h;
int a[260][260];
bool vis[260][260][6];
int dx[4] = {0,1,0,-1}, dy[4]={1,0,-1,0};

enum BLOCKS {
    TRAP = -2,
    WALL,
    EMPTY,
};

class Node {
public:
    pair<int, int> pos;
    int time;
    int health;

    bool operator<(const Node &other) const {
        return time == other.time ? health > other.health : time > other.time;
    }

    Node(int x = 0, int y = 0, int t = 0, int h = 0) : pos({x, y}), time(t), health(h) {}
};

priority_queue<Node> pq;

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m >> h;
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) {
                char tmp;
                cin >> tmp;
                if (tmp == '.') a[i][j] = EMPTY;
                if (tmp == '#') a[i][j] = WALL;
                if (tmp == '*') a[i][j] = TRAP;
            }
        int ans = -1;
        pq.push(Node(1,1,0,h));
        while(!pq.empty()) {
            Node cur = pq.top(); pq.pop();
            int &x = cur.pos.first, &y = cur.pos.second;
            if(x == n && y == m) {
                ans = cur.time;
                break;
            }
            for(int d=0; d<4; d++) {
                int nx = x+dx[d], ny = y+dy[d];
                if(nx < 1 || ny < 1 || nx > n || ny > m) continue;
                if(a[nx][ny] == WALL) continue;
                if(a[nx][ny] == TRAP && cur.health <= 1) continue;  // 不能踩了
                if(!vis[nx][ny][cur.health-(a[nx][ny]==TRAP)]) {
                    vis[nx][ny][cur.health-(a[nx][ny]==TRAP)] = true;
                    pq.push(Node(nx, ny, cur.time+1, cur.health-(a[nx][ny]==TRAP)));
                }
            }
        }
        cout << ans << endl;
    }
}