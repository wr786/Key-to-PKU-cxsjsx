#include <iostream>
#include <algorithm>

using namespace std;
int n;
int dp[10001][2];  // 到t时间为止能获得的最高分数，t天有没有做作业
int DDL;

struct Course {
    int score;
    int ddl;

    bool operator<(const Course &other) const {
        return ddl == other.ddl ? score > other.score : ddl < other.ddl;
    }

    Course(int s=0, int d=0) : score(s), ddl(d) {}
} courses[10001];

int main() {
    cin >> n;
    for(int i=1; i<=n; i++)
        cin >> courses[i].score >> courses[i].ddl,
        DDL = max(DDL, courses[i].ddl);
    sort(courses+1, courses+1+n);
    dp[0][1] = -0x3f3f3f3f;
    for(int c=1; c<=n; c++) {
        for(int t=courses[c].ddl; t; t--) {
            dp[t][0] = max(dp[t][0], max(dp[t-1][0], dp[t-1][1]));
            dp[t][1] = max(dp[t][1], dp[t][0]+courses[c].score);
        }
    }
    int ans = 0;
    for(int i=1; i<=DDL; i++) {
        ans = max(ans, max(dp[i][1], dp[i][0]));
    }
    cout << ans << endl;
}
