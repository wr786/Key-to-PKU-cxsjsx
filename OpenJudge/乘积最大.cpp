#include <iostream>
#include <string>
using namespace std;
int n, k;
string str;
int num[41][41];
int dp[41][41][7];  // startPos, length, #×

inline int getNum(int start, int len) {
    if(num[start][len]) return num[start][len];
    return num[start][len] = atoi(str.substr(start, len).c_str());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k >> str;
    for(int span=1; span<=n; span++) {
        for(int beg=0; beg<=n-span; beg++) {
            dp[beg][span][0] = getNum(beg, span);
            for(int multi=1; multi<=k; multi++) {
                for(int insertDist=1; insertDist<span; insertDist++) {
                    dp[beg][span][multi] = max(dp[beg][span][multi], dp[beg][insertDist][multi-1]*getNum(beg+insertDist, span-insertDist));
                }
            }
        }
    }
    cout << dp[0][n][k] << endl;
    return 0;
}