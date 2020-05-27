#include <iostream>
#include <cctype>
using namespace std;
int n, k;
int chessboard[8][8];
bool viscol[8];  // 不能摆放在同一列
int ans;

void dfs(int row, int chessLeft) { // 每行选取一个，这样就不用考虑行的重复问题了
    if(!chessLeft) {ans++; return;}
    if(row == n) {return;}
    for(int i=0; i<n; i++) {
        if(chessboard[row][i] && !viscol[i]) {
            // 下棋在这
            viscol[i] = true;
            dfs(row+1, chessLeft-1);
            viscol[i] = false;
        }
    }
    // 这行不下棋
    dfs(row+1, chessLeft);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    while(cin >> n >> k) {
        if(n == -1) return 0;
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++) {
                char tmp; cin >> tmp;
                while(isspace(tmp)) cin >> tmp;
                if(tmp == '#') chessboard[i][j] = 1;
                else chessboard[i][j] = 0;
            }
        fill(viscol, viscol+8, 0);
        ans = 0;
        dfs(0, k);
        cout << ans << endl;
    }
}