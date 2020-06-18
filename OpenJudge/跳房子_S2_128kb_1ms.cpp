#include <iostream>
#include <string>
#include <queue>
#include <cstring>

using namespace std;
int n, m;
bool vis[10006];

struct Node {
    int pos;
    int op;
    int len;

    bool operator<(const Node &other) const {
        return len == other.len ? op > other.op : len > other.len;   // dict order
    }

    Node(int x = 0, int o = 0, int l = 0) : pos(x), op(o), len(l) {}
};

priority_queue<Node> pq;

int main() {
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        while (!pq.empty()) pq.pop();
        memset(vis, false, sizeof(vis));
        pq.push(Node(n));
        vis[n] = true;
        while (!pq.empty()) {
            Node cur = pq.top();
            pq.pop();
            if (cur.pos <= 0) continue;
            if (cur.pos == m) {
                cout << cur.len << endl;
                for (int i = cur.len - 1; i >= 0; i--) {
                    cout << "HO"[(cur.op & (1 << i)) ? 1 : 0];
                }
                cout << endl;
                break;
            }
            if (cur.len >= 25) continue; // prune
            if (cur.pos * 3 <= 10005 && !vis[cur.pos * 3]) {
                pq.push(Node(3 * cur.pos, cur.op << 1, cur.len + 1));
                vis[cur.pos * 3] = true;
            }
            if (!vis[cur.pos / 2] && cur.pos / 2 != 0) {
                pq.push((Node(cur.pos / 2, (cur.op << 1) | 1, cur.len + 1)));
                vis[cur.pos / 2] = true;
            }
        }
    }
    return 0;
}