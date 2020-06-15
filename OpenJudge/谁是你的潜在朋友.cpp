#include <iostream>
#include <unordered_map>
using namespace std;
unordered_map<int, int> cnt;
int peo[201];

int main() {
    int n, m; cin >> n >> m;
    for(int i=1; i<=n; i++) {
        cin >> peo[i];
        cnt[peo[i]]++;
    }
    for(int i=1; i<=n; i++) {
        if(cnt[peo[i]] > 1) {
            cout << cnt[peo[i]]-1 << endl;
        } else {
            cout << "BeiJu\n";
        }
    }
    return 0;
}