#include<iostream>
#include<algorithm>
#include<string>
#include<cctype>
using namespace std;
int n, c;
int stalls[100001];

inline void readIn(int& x) {
    x = 0;
    char c = getchar();
    while(isspace(c)) c = getchar();
    while(!isspace(c)) {
        x = 10 * x + c - '0';
        c = getchar();
    }
}

bool check(int span) {
    // 显然第一个摊位是必选的
    int cows = 1;
    int last = stalls[1];
    for(int i=2; i<=n; i++) {
        // 显然需要尽量贪心地选取，满足条件就选
        if(stalls[i] - last >= span) {
            cows++;
            last = stalls[i];
            if(cows >= c) return true;
        }
    }
    return false;
}

int main() {
    readIn(n); readIn(c);
    for(int i=1; i<=n; i++) readIn(stalls[i]);
    sort(stalls+1, stalls+1+n); // 从小到大排序，便于二分查找
    int l=0, r=stalls[n]-stalls[1];   // 上限肯定是横跨俩
    while(l < r) {
        int mid = (l+r+1)/2;
        if(check(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    cout << l << endl;
}