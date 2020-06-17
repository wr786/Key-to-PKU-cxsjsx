#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#include <vector>
#include <unordered_map>

using namespace std;
int m, n;
int a[101][101];
int vis[101][101];  // 记录到达这里的线索数，如果线索数相同相当于白走了
int curKeyMax;  // 显然，找到一个key后，就不用考虑比这个key小的了
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

struct Node {
    pair<int, int> pos;
    int costTime;
    int keys;   // 线索
    bool operator<(const Node &other) const {
        return costTime == other.costTime ? keys < other.keys : costTime > other.costTime;
    }

    Node(int x, int y, int t, int k) : pos({x, y}), costTime(t), keys(k) {}
};

priority_queue<Node> pq;
enum BLOCKS {
    WALL = 0,
    PATH
};

inline bool check_boundary(int x, int y) {
    return (x >= 1 && y >= 1 && x <= m && y <= n);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> m >> n;
        int ans = -1;
        vector<int> Keys;
        unordered_map<int, int> keymap; int idx = 1;
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++) {
                cin >> a[i][j];
                if(a[i][j] > 1) Keys.push_back(a[i][j]);
            }
        sort(Keys.begin(), Keys.end()); // 映射keys到对应的顺序
        for(auto& k: Keys) {
            keymap[k] = ++idx;
        }
        while (!pq.empty()) pq.pop();
        pq.push(Node(1, 1, 0, 1));
        vis[1][1] = 1;
        curKeyMax = 1;
        while (!pq.empty()) {
            Node cur = pq.top();
            pq.pop();
            int & x = cur.pos.first, & y = cur.pos.second;
            if(keymap[a[x][y]] == cur.keys + 1) {
                cur.keys++;
                if (cur.keys == idx) {
                    ans = cur.costTime;
                    break;
                }
            }
            if(cur.keys < curKeyMax) continue;  // 没这个剪枝必然TLE
            else curKeyMax = cur.keys;
            //! 不过仔细想想，建议直接写idx个bfs，每次都只专心找一个key，这样应该能够更快（指省去了加入pq的时间
            for(int dir=0; dir<4; dir++) {
                int nx = x + dx[dir], ny = y + dy[dir];
                if(check_boundary(nx, ny) && a[nx][ny] != WALL) {
                    if(vis[nx][ny] < cur.keys) {
                        vis[nx][ny] = cur.keys;
                        pq.push(Node(nx, ny, cur.costTime+1, cur.keys));
                    }
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}