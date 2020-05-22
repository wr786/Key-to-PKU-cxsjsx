#include <iostream>
#include <algorithm>
using namespace std;

int a[201];
int flag[201];
int f[10001];   // 能凑成_的方案数
int g[201][10001];   // 不使用_凑成_的方案数 
int cnt;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n,x; cin >> n >> x;
    for(int i=1; i<=n; i++) cin >> a[i];
    f[0] = 1;   // 01背包
    for(int i=1; i<=n; i++)
        for(int j=x; j>=a[i]; j--) {
            f[j] += f[j-a[i]];
        }
    for(int i=1; i<=n; i++) {  
        for(int j=0; j<=x; j++) {
            if(j < a[i]) g[i][j] = f[j];    // 必不可能用到
            else g[i][j] = f[j] - g[i][j-a[i]]; // 容斥原理，不使用的数量==总量-使用的数量
        }
        if(g[i][x] == 0) {
            flag[i] = true;
            cnt ++ ;
        }
    }    
    cout << cnt << endl;
    bool outputFlag = false;
    for(int i=1; i<=n; i++) {
        if(flag[i]) {
            if(outputFlag) cout << " ";
            cout << a[i];
            outputFlag = true;
        }
    }
    cout << endl;
}