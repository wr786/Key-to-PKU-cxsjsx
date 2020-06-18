#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#define eps 1e-6
bool flag;
vector<int> ans;
int n;

void dfs(double sum, int left, int lim) {
    if(flag) return;
    if(fabs(sum - 1.0) <= eps && !left) {
        cout << ans.size();
        for(auto& item: ans) {
            cout << " " << item;
        }
        cout << endl;
        flag = true;
        return;
    }
    if(sum >= 1 + eps) return;
    if(left <= 0) return;
    for(int i=lim; i<=left; i++) {
        if(sum + 1.0 / i >= 1 + eps) continue;
        ans.push_back(i);
        dfs(sum + 1.0 / i, left-i, i);
        ans.pop_back();
        if(flag) return;
    }
}

int main() {
    int t; cin >> t;
    while(t--) {
        cin >> n;
        flag = false;
        ans.clear();    // init
        dfs(0, n, 1);
        if(!flag) cout << -1 << endl;
    }
    return 0;
}