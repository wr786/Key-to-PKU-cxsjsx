// https://2d.hep.com.cn/187723/9
// qwq，程设正态预定
#include <iostream>
#include <algorithm>
#include <queue>
#include <limits>
using namespace std;
const int INF = numeric_limits<int>::max(); // INT_MAX
#define MAXL 1000010
bool hasCow[MAXL];
int dp[MAXL];   // 考虑从0~MAXL需要几个水龙头覆盖
struct Node {
    int pos;
    int cnt;
    bool operator < (const Node& other) const {
        return cnt == other.cnt? pos > other.pos : cnt > other.cnt;
    }
    Node(int p=0, int c=0): pos(p), cnt(c) {}
};
int n, l;
int A, B;
priority_queue<Node> pq;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> l;
    cin >> A >> B; A<<=1; B<<=1;
    while(n--) {
        int s, e; cin >> s >> e;
        for(int i=s+1; i<e; i++)    // 开区间
            hasCow[i] = true;
    }
    fill(dp, dp+1+l, INF);  // init
    // 初始化dp边界（只用一个水龙头的情形）
    for(int i=A; i<=B; i+=2) {
        if(!hasCow[i]) {    // 边界区必不有牛
            dp[i] = 1;
            if(i <= B+2 - A) {  // 维护优先队列中只有[i-B, i-A]的元素
                pq.push(Node(i, 1));
            }
        }
    }
    for(int i=B+2; i<=l; i+=2) {
        if(!hasCow[i]) {
            Node last;
            while(!pq.empty()) {
                last = pq.top();
                if(last.pos < i - B) pq.pop();
                else break;
            }  // 筛选掉范围之外的
            if(!pq.empty()) { // 那么last就是符合范围条件的
                dp[i] = last.cnt+1; // 递推
            }
        }
        if(dp[i+2-A] != INF) {  // 存在解，那就为之后的点加入维护
            pq.push(Node(i+2-A, dp[i+2-A]));
        }
    }
    if(dp[l] == INF) cout << -1 << endl;
    else cout << dp[l] << endl;
    return 0;
}