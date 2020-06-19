#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <cctype>
#include <limits>
#include <cmath>
using namespace std;
const int INF = numeric_limits<int>::max();
int n, m;
int a[101][101];
int vis[101][101];
int dx[4] = {0,1,0,-1}, dy[4] ={1,0,-1,0};

enum BLOCKS {
    WALL = -2,
    EMPTY = -1,
    EXIT = 0,
};

struct Node {
    pair<int,int> pos;
    int time;
    bool operator < (const Node& other) const {
        return time > other.time;
    }
    Node(int x=0, int y=0, int t=0):pos({x, y}),time(t){}
};

priority_queue<Node> pq;

int main() {
    int T; cin >> T;
    for(int t=1; t<=T; t++) {
        cout << "Case #" << t << ": ";
        cin >> n >> m;
        int sx, sy;
        for(int i=1; i<=n ;i++)
            for(int j=1; j<=m; j++) {
                char tmp; cin >> tmp;
                if(tmp == '.') a[i][j] = EMPTY;
                else if(tmp == '#') a[i][j] = WALL;
                else if(tmp == 'B') a[i][j] = EXIT;
                else if(tmp == 'I') {
                    sx = i;
                    sy = j;
                    a[i][j] = EMPTY;
                } else {
                    a[i][j] = tmp - 'a' + 1;    // portal
                }
                vis[i][j] = INF;
            }
        int ans = -1;
        while(!pq.empty()) pq.pop();
        pq.push(Node(sx, sy, 0));
        while(!pq.empty()) {
            Node cur = pq.top(); pq.pop();
            int &x = cur.pos.first, &y= cur.pos.second;
            if(a[x][y] == EXIT) {
                ans = cur.time;
                break;
            }
            if(a[x][y] > 0) {   // portal
                for(int i=1; i<=n; i++)
                    for(int j=1; j<=m; j++) {
                        if(a[i][j] == a[x][y]) {
                            if(vis[i][j] > cur.time+1) {
                                vis[i][j] = cur.time+1;
                                pq.push(Node(i, j, cur.time+1));
                            }
                        }
                    }
            }
            for(int d=0; d<4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if(nx < 1 || ny < 1 || nx > n || ny > m) continue;
                if(a[nx][ny] == WALL) continue;
                if(vis[nx][ny] > cur.time + 1) {
                    vis[nx][ny] = cur.time + 1;
                    pq.push(Node(nx, ny, cur.time+1));
                }
            }
        }
        cout << ans << endl;
    }
}