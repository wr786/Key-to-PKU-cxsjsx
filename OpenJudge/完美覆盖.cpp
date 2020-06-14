#include <iostream>
using namespace std;
int vis[32];

int fn(int x) {
    if(x == 0)
        return 1;
    if(x == 1)
        return 0;
    if(x == 2)
        return 3;
    if(vis[x]) return vis[x];
    int ret = 3 * fn(x-2);  // 标准形1
    for(int i=4; i<=x; i+=2) {
        ret += 2 * fn(x-i);
    }
    return vis[x] = ret;
}

int main() {
    int n;
    while(cin >> n, n!=-1) {
        cout << fn(n) << endl;
    }
}