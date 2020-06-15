#include <iostream>
#include <algorithm>

using namespace std;
int vis[101][11];
int n, m;

int DP(int floorLeft, int eggNum) {
    if (floorLeft == 0) return 0;
    if (eggNum == 1) return floorLeft;
    if (vis[floorLeft][eggNum] != 0x3f3f3f3f) return vis[floorLeft][eggNum];
    int ret = 0x3f3f3f3f;
    for (int dropFloor = 1; dropFloor <= floorLeft; dropFloor++) {
        ret = min(ret, max(DP(dropFloor - 1, eggNum - 1), DP(floorLeft - dropFloor, eggNum)) + 1);
    }   // 前一个代表鸡蛋碎了，于是只要从丢下去的这层楼之下的楼中找;后一个代表没碎。
    return vis[floorLeft][eggNum] = ret;
}

int main() {
    while (cin >> n >> m) {
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++)
                vis[i][j] = 0x3f3f3f3f;
        cout << DP(n, m) << endl;
    }
}