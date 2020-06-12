#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;
#define INF 0x3f3f3f3f
int dp[101][1001];  // assume width<=1000; (_,_) => (curidx,curWidth)
struct Device {
    int price = 0;
    int width = 0;
} devices[101][101];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        for(int i=1; i<=n; i++) {
            int m; cin >> m; // size
            for(int j=0; j<=1000; j++)
                dp[i][j] = INF; // init
            for(int j=1; j<=m; j++) {
                cin >> devices[i][j].width >> devices[i][j].price;
                if(i == 1) {
                    dp[i][devices[i][j].width] = devices[i][j].price;
                    continue;
                }
                for(int w=0; w<=1000; w++) {    // width should be not negative
                    if(dp[i-1][w] != INF) {
                        if(devices[i][j].width >= w) { 
                            dp[i][w] = min(dp[i][w], dp[i-1][w]+devices[i][j].price);
                        } else {
                            dp[i][devices[i][j].width] = min(dp[i][devices[i][j].width], dp[i-1][w]+devices[i][j].price);
                        }
                    }
                }
            }
        }
        double ans = 0;
        for(int i=1; i<=1000; i++)  {
            if(dp[n][i] != INF)
                ans = max(ans, (double)i/(double)dp[n][i]);
        }
        cout << fixed << setprecision(3) << ans << endl;
    }
    return 0;
}