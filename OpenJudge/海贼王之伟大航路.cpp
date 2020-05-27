#include <cstdio>
#include <algorithm>
#include <cctype>
using namespace std;
int graph[20][20];
int n;
int ans = 0x3f3f3f3f;
int remem[20][1<<16];  // 用来存之前到达这个状态要花多久

inline void readIn(int& x) {
    x = 0;
    char c = getchar();
    while(isspace(c)) c = getchar();
    while(!isspace(c)) {
        x = x * 10 + c - '0';
        c = getchar();
    }
}

void dfs(int pos, int viewed, int time) {   // 状压DFS
    if(!remem[pos][viewed] || time < remem[pos][viewed]) {
        remem[pos][viewed] = time;
    } else return;  // 如果到达现在这个阶段都比之前要花的久，那更别提后面的了
    if(time >= ans) return; // prune
    if(pos == n) {
        if(viewed == (1<<n)-1) { // 遍历诸岛
            ans = min(ans, time);
        }
        return; // 因为不能反复一个岛，所以到n必然就已经是终点了
    }
    for(int i=0; i<n; i++) {
        if(!((1<<i) & viewed)) {    // 还没去过
            dfs(i+1, viewed|(1<<i), time+graph[pos][i+1]);
        }
    }
}

int main() {
    readIn(n);
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            readIn(graph[i][j]);
    dfs(1, 1, 0);
    printf("%d\n", ans);
    return 0;
}