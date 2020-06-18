#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
int n, m;
int a[101][101];
bool vis[101][101][260];
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
enum BLOCK {
    STONE = -1,
    EMPTY,
    EXIT,
    // 训练师
    RIGHT,
    DOWN,
    LEFT,
    UP,
};

struct Trainer {
    pair<int, int> pos;
    int face;

    Trainer(int x = 0, int y = 0, int f = 0) : pos({x, y}), face(f) {}
} trainers[9];

int tidx = 0;   // trainer的总数
struct Node {
    pair<int, int> pos;
    int time;
    int beated;

    bool operator<(const Node &other) const {
        return time == other.time ? beated < other.beated : time > other.time;
    }

    Node(int x = 0, int y = 0, int t = 0, int b = 0) : pos({x, y}), time(t), beated(b) {}
};

priority_queue<Node> pq;

int main() {
    cin >> n >> m;
    int sx = 1, sy = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            char tmp;
            cin >> tmp;
            if (tmp == 'I') {
                sx = i, sy = j;
                a[i][j] = EMPTY;
            } else if (tmp == '.') a[i][j] = EMPTY;
            else if (tmp == '#') a[i][j] = STONE;
            else if (tmp == 'O') a[i][j] = EXIT;
            else {
                if (tmp == 'a') a[i][j] = LEFT;
                else if (tmp == 'w') a[i][j] = UP;
                else if (tmp == 's') a[i][j] = DOWN;
                else if (tmp == 'd') a[i][j] = RIGHT;
                trainers[++tidx] = Trainer(i, j, a[i][j]);
            }
        }
    int ans = -1;
    pq.push(Node(sx, sy, 0, 0));
    vis[sx][sy][0] = true;
    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();
        int &x = cur.pos.first, &y = cur.pos.second;
        if (a[x][y] != EMPTY && a[x][y] != EXIT) continue;   // 不能走的地方
        for (int i = 0; i < tidx; i++) {
            if (!(cur.beated & (1 << i))) {
                // 需要打
                int &tx = trainers[i + 1].pos.first, &ty = trainers[i + 1].pos.second;
                // 必须要在同一条直线上才能对战
                if (tx == x) {
                    if (y > ty && trainers[i + 1].face == RIGHT) {
                        bool flag = true;
                        for(int Y=ty+1; Y<y; Y++) {
                            if(a[x][Y] != EMPTY && a[x][Y] != EXIT) {   // 视线被阻挡
                                flag = false;
                                break;
                            }
                        }
                        if(flag)
                            cur.beated |= (1 << i);
                    } else if (y < ty && trainers[i + 1].face == LEFT) {
                        bool flag = true;
                        for(int Y=y+1; Y<ty; Y++) {
                            if(a[x][Y] != EMPTY && a[x][Y] != EXIT) {   // 视线被阻挡
                                flag = false;
                                break;
                            }
                        }
                        if(flag)
                            cur.beated |= (1 << i);
                    }
                } else if (ty == y) {
                    if (x > tx && trainers[i + 1].face == DOWN) {
                        bool flag = true;
                        for(int X=tx+1; X<x; X++) {
                            if(a[X][y] != EMPTY && a[X][y] != EXIT) {   // 视线被阻挡
                                flag = false;
                                break;
                            }
                        }
                        if(flag)
                            cur.beated |= (1 << i);
                    } else if (x < tx && trainers[i + 1].face == UP) {
                        bool flag = true;
                        for(int X=x+1; X<tx; X++) {
                            if(a[X][y] != EMPTY && a[X][y] != EXIT) {   // 视线被阻挡
                                flag = false;
                                break;
                            }
                        }
                        if(flag)
                            cur.beated |= (1 << i);
                    }
                }
            }
        }   // 先处理对战
        vis[x][y][cur.beated] = true;   // 更新训练师
        if (a[x][y] == EXIT && cur.beated == (1 << tidx) - 1) {
            ans = cur.time;
            break;
        }
//        cout << x << " " << y << " " << cur.time <<" " << cur.beated << endl;
        for(int d=0; d<4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if(nx < 1 || ny < 1 || nx > n || ny > m) continue;
            if(a[nx][ny] != EMPTY && a[nx][ny] != EXIT) continue;
            if(!vis[nx][ny][cur.beated]) {
                vis[nx][ny][cur.beated] = true;
                pq.push(Node(nx, ny, cur.time+1, cur.beated));
            }
        }
    }
    cout << ans << endl;
    return 0;
}
