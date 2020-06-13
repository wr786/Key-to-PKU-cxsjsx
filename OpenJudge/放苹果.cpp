#include<iostream>
using namespace std;
int vis[15][15];

int dp(int m, int n) {
    if(m == 0) return 1;
    if(n == 1) return 1;
    if(vis[m][n]) return vis[m][n];
    vis[m][n] = dp(m, n-1);
    if(m >= n) vis[m][n] += dp(m-n, n);
    return vis[m][n];
}

int main () {
    int t; cin >> t;
    while(t--) {
        int m, n; cin >> m >> n;
        cout << dp(m, n) << endl;
    }
}