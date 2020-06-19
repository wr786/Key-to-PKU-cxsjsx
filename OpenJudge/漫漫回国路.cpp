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
int n;
int a[20][20];
int vis[(1<<10)];
bool flag = false;

void dfs(int pos) {
    vis[pos] = 1;
    if(pos == n) {
        flag = true;
        return;
    }
    for(int i=1; i<=n; i++) {
        if(!vis[i] && a[pos][i] > 0) {
            dfs(i);
            if(flag ) return;
        }
    }
}

int main() {
    int t; cin >> t;
    while(t--) {
      cin >> n;
      flag = false;
      memset(vis, 0, sizeof(vis));
      for(int i=1; i<=n;i++)
          for(int j=1; j<=n; j++)
              cin >> a[i][j];
        vis[1] = 1;
        dfs(1);
        cout << (flag?"YES":"NO") << endl;
    }
}