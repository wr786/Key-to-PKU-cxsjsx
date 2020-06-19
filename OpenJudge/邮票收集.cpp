#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <cctype>
#include <limits>
using namespace std;
const int INF = numeric_limits<int>::max();
int n, k;
int a[1001];
int ans;

void dfs(int pos, int tar, int cnt) {
    if(tar == 0) {
        ans = min(ans, cnt);
        return;
    }
    if(pos <= 0) {
        return;
    }
    if(cnt >= ans) return;
    for(int i=0; i<=tar/a[pos]; i++)
        dfs(pos-1, tar-i*a[pos], cnt+i);
}

int main() {
    while(cin >> n >> k) {
        if(n == 0 && k == 0) break;
        for(int i=1; i<=n; i++)
            cin >> a[i];
        ans = INF;
        dfs(n, k, 0);
        cout << (ans==INF?-1:ans) << endl;
    }
    return 0;
}