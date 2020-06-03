#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int a[5][5];
string ans;
int minWay = 0x3f3f3f3f;

void bfs(int x, int y, string way, int steps) {
    if(x == 4 && y == 4) {
        if (steps < minWay) {
            minWay = steps;
            ans = way;
        }
    } else {
        // 向下
        if(x < 4 && !a[x+1][y]) {
            bfs(x+1, y, way+to_string(10*(x+1)+y), steps+1);
        }
        // 向右
        if(y < 4 && !a[x][y+1]) {
            bfs(x, y+1, way+to_string(10*x+y+1), steps+1);
        }
    }
}

int main() {
    ios::sync_with_stdio((false)); cin.tie(0);
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            cin >> a[i][j];
    bfs(0,0, "00", 0);
    int l = ans.length();
    for(int i=0; i<l/2; i++) {
        cout << "(" << ans[i<<1] << ", " << ans[i<<1|1] << ")\n";
    }
    return 0;
}