#include <iostream>
#include <valarray>
using namespace std;

int N, M;
valarray<int> cost;

bool judgeOK(int div) {
    int rem = 0, cnt = 0;
    for(int i=0; i<N; i++) {
        if(rem + cost[i] <= div) {
            rem += cost[i];
        } else {
            rem = cost[i];
            cnt++;
            if(cnt > M) return false;
        }
    }
    cnt += rem > 0;
    return cnt <= M;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M;
    cost.resize(N);
    for(int i=0; i<N; i++) cin >> cost[i];
    int l = cost.max(), r = 2e8;    // 反正应该是个大数字
    while(l < r) {
        int mid = (l + r) >> 1;
        if(judgeOK(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << r << endl;
    return 0;
}