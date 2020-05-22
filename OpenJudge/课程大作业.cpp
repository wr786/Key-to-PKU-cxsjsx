#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
#define MAX 1<<15   
// 状压DP
struct DDL {
    string className = "";
    int ddl = 0;
    int costTime = 0;
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;    
    while(t--) {
        int n; cin >> n;
        DDL* ddlList = new DDL[n];
        int sum[MAX];   // 完成_这些ddl总共所需要的时间（如果想要尽量少扣分，当然要马不停蹄地做了
        int dp[MAX];    // 最少扣分
        string ans[MAX];// 用于输出答案
        for(int i=0; i<n; i++) {
            cin >> ddlList[i].className >> ddlList[i].ddl >> ddlList[i].costTime;
            sum[(1<<i)] = ddlList[i].costTime;
        }
        for(int i=0; i<(1<<n); i++) {
            for(int j=0; j<n; j++) {
                if(i & (1<<j)) {
                    sum[i] = sum[i^(1<<j)] + ddlList[j].costTime;
                }
            }
        }
        dp[0] = 0;
        for(int i=0; i<(1<<n); i++) {   // 至少要完成一个ddl吧，所以就从1开始
            for(int j=0; j<n; j++) {
                if(i & (1<<j)) { 
                    if(dp[i^(1<<j)] + max(0, sum[i] - ddlList[j].ddl) <= dp[i] || ans[i] == "") {   // 如果这样减分更少，或者还没有这样过
                        if(dp[i^(1<<j)] + max(0, sum[i] - ddlList[j].ddl) < dp[i] || ans[i] == "" || ans[i] > ans[i^(1<<j)] + ddlList[j].className + '\n') {
                            ans[i] = ans[i^(1<<j)] + ddlList[j].className + '\n';
                        }
                        dp[i] = dp[i^(1<<j)] + max(0, sum[i] - ddlList[j].ddl);    
                    }
                }
            }
        }
        // 到最后必须完成全部ddl啊！
        cout << dp[(1<<n)-1] << endl;
        cout << ans[(1<<n)-1];
    }
}