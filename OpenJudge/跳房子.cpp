#include <iostream>
#include <string>
#include <limits>
using namespace std;
string ans;
string tmp;
int minT;

void dfs(int cur, int tar) {
    if(!cur) return;
    if(cur > 10000) return;
    if(cur == tar) {
        if(tmp.length() < minT) {
            // 选取方法必然字典序
            ans = tmp;
            minT = ans.length();
        }
        return;
    }
    if(tmp.length() >= minT) return;    // prune
    if(tmp.length() >= 25) return;  // prune
    tmp = tmp + "H";
    dfs(3*cur, tar);
    tmp = tmp.substr(0, tmp.length()-1);
    tmp = tmp + "O";
    dfs(cur/2, tar);
    tmp = tmp.substr(0, tmp.length()-1);
}

int main() {
    int n, m;
    while(cin >> n >> m, n||m) {
        minT = numeric_limits<int>::max();
        tmp = "";
        dfs(n, m);
        cout << minT << endl << ans << endl;
    }
}