// 树洞 #1453833
#include <iostream>
#include <algorithm>
using namespace std;
int n;
bool m[301][301];
bool f[301][301], g[301][301];
// f代表i能否在i~j中获胜，g代表j能否在i~j中获胜

int main() {
    cin >> n;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++) {
            char tmp ; cin >> tmp;
            m[i][j] = tmp != 'L';
        }
    for(int i=1; i<=n; i++)
        f[i][i] = g[i][i] = true;   // init
    for(int span=2; span<=n; span++) {
        for(int i=1; i<=n-span+1; i++) {
            int j = i + span - 1;
            for(int k=i; k<j && !f[i][j]; k++) {
                f[i][j] |= (f[i][k] & f[k+1][j] & (m[i][k+1] | m[k][k+1]));
                f[i][j] |= (f[i][k] & g[k+1][j] & (m[i][j] | m[k][j]));
            }
            for(int k=i; k<j && !g[i][j]; k++) {
                g[i][j] |= (g[i][k] & g[k+1][j] & (m[j][k] | m[k+1][k]));
                g[i][j] |= (f[i][k] & g[k+1][j] & (m[j][i] | m[k+1][i]));
            }
        }
    }
    bool output_flag = false;
    for(int k=1; k<=n; k++) {
        if(g[1][k] & f[k][n]) {
            if(output_flag) cout << " ";
            cout << k;
            output_flag = true;
        }
    }
}