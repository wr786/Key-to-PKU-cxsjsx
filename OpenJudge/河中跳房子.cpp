#include <iostream>
#include <valarray>
using namespace std;

int L, N, M;
valarray<int> stones;

bool judgeOK(int div) {
    int cnt = 0;
    for(int i=0; i<N+2; i++) {
        for(int j=i+1; j<N+2; j++) {
            if(stones[j] - stones[i] < div) {
                // 要被移去的石头
                cnt++;
            } else {
                // 从贪心的角度，这里就不应该移去了
                i = j-1;
                break;
            }
            if(j == N+1) {
                // 到终点了
                i = j;
                break;
            }
        }
    }
    return cnt <= M;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> L >> N >> M;
    stones.resize(N+2);
    stones[0] = 0; stones[N+1] = L;
    for(int i=1; i<=N; i++) 
        cin >> stones[i];
    int l = 0, r = L;
    while(l < r) {
        int mid = (l + r + 1) >> 1;
        if(judgeOK(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    cout << l << endl;
    return 0;
}