#include <iostream>
#include <valarray>
#include <cmath>
using namespace std;
#define PI 3.14159265358979323846

int N, M;
valarray<double> pies;

bool judgeOK(double div) {
    int cnt = 0;
    for(int i=0; i<N; i++) {
        cnt += floor(pies[i] / div );    // 利用整除
    }
    return cnt >= M;
}

int main() {
    // freopen("in.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M;
    pies.resize(N);
    M++;    // “我”也要吃pie
    for(int i=0; i<N; i++) {
        cin >> pies[i];
        pies[i] = PI * pies[i] * pies[i];
    }
    // 将过程放大10000倍（便于四舍五入
    double l = 0, r = pies.sum() / M;   // 最大肯定是均分
    while(l < r) {
        double mid = (l + r + 0.0001) * 0.5;
        if(judgeOK(mid)) {
            l = mid;
        } else {
            r = mid-0.0001;
        }
    }
    // cout << l / 100000 << "." << round(l % 100000 / 100.0) << endl;  // 假装是浮点数
    printf("%.3lf", l);
    return 0;
}