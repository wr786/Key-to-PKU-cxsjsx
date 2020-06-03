#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <cctype>
#include <unordered_map>
#include <cmath>
using namespace std;
int n, m;
int ans;
int map[105][105];
int vis[105][105][10][32];
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
unordered_map<int, int> snakeID;
int idx;

enum cellType {
    TRAP = -4,
    SNAKE,
    SUN,
    MONK,
    EMPTY,
};  // 用来标记地图类型

struct node {
    int x;
    int y;
    int time;
    int keys;
    int killed;
    bool operator < (const node& other) const {
        if(time == other.time) return keys < other.keys;
        return time > other.time;
    }
};

inline int getType(const node& N) {
    return map[N.x][N.y];
}

int main() {
    ios::sync_with_stdio((false)); cin.tie(0);
    while(cin >> n >> m) {
        if(!n && !m) break;
        ans = 0x3f3f3f3f;
        snakeID.clear();
        idx = 0;
        int startx=1, starty=1;
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++) {
                char c; cin >> c;
                while(isspace(c)) cin >> c;
                if(c == '.') map[i][j] = EMPTY;
                else if(c == '#') map[i][j] = TRAP;
                else if(c == 'S') {
                    map[i][j] = SNAKE;
                    snakeID[i*100+j] = idx++;
                }
                else if(c == 'K') {
                    map[i][j] = SUN;
                    startx = i, starty = j;
                }
                else if(c == 'T') map[i][j] = MONK;
                else map[i][j] = c - '0';   // KEY
                for(int k=0; k<=m; k++)
                    for(int l=0; l<32; l++)
                        vis[i][j][k][l] = 0;
            }

        priority_queue<node, vector<node>, less<node> > nodes;
        nodes.push({startx, starty, 0, 0, 0});
        while(!nodes.empty()) {
            node curNode = nodes.top();
            nodes.pop();
            if(curNode.time >= ans) continue;
            if(vis[curNode.x][curNode.y][curNode.keys][curNode.killed]) continue;
            vis[curNode.x][curNode.y][curNode.keys][curNode.killed] = 1;
            if(curNode.time >= ans) continue;
            if(getType(curNode) == TRAP) continue;
            if(getType(curNode) == SNAKE) {
                if((curNode.killed & (1<<snakeID[curNode.x*100+curNode.y])) == 0 ) {
                    curNode.time++;
                    curNode.killed |= (1<<snakeID[curNode.x*100+curNode.y]);
                }
            }
            if(getType(curNode) > 0) {  // kaki
                if(curNode.keys == getType(curNode) - 1)
                    curNode.keys = getType(curNode);
            }
            if(curNode.keys == m && getType(curNode) == MONK) {
                ans = min(ans, curNode.time);
                continue;
            }
            for(int dir=0; dir<4; dir++) {
                int nx = curNode.x + dx[dir], ny = curNode.y + dy[dir];
                if(nx && ny && nx <=n && ny <= n && map[nx][ny] != TRAP) {
                    nodes.push({nx, ny, curNode.time+1, curNode.keys, curNode.killed});
                }
            }
        }

        if(ans == 0x3f3f3f3f) cout << "impossible";
        else cout << ans;
        cout << "\n";
    }
    return 0;
}