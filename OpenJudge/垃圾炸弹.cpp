#include<iostream>
#include<algorithm>
using namespace std;
int mapu[1050][1050];
int presum[1050][1050]; // 前缀和，以右下角为标记
int radius;

inline int getPresum(int x, int y) {
    if(x < 1 || y < 1) return 0;
    if(x > 1025 && y <= 1025) return presum[1025][y];
    if(y > 1025 && x <= 1025) return presum[x][1025];
    if(x > 1025 && y > 1025) return presum[1025][1025];
    return presum[x][y];
}

int main() {
    cin >> radius;
    int boomCnt; cin >> boomCnt;
    for(int i=0; i<boomCnt; i++) {
        int x, y, cnt; cin >> x >> y >> cnt;
        mapu[x+1][y+1] = cnt;
    }
    for(int i=1; i<=1025; i++)
        for(int j=1; j<=1025; j++) {
            presum[i][j] = presum[i-1][j] + presum[i][j-1] - presum[i-1][j-1] + mapu[i][j];
        }
    int ansCnt=0, ansSum=0;
    for(int i=1; i<=1025; i++) {
        for(int j=1; j<=1025; j++) {
            // 确定中心
            // int curSum = presum[i+radius][j+radius] - presum[i-radius-1][j+radius] - presum[i+radius][j-radius-1] + presum[i-radius-1][j-radius-1];
            int curSum = getPresum(i+radius, j+radius) - getPresum(i-radius-1, j+radius) - getPresum(i+radius, j-radius-1) + getPresum(i-radius-1, j-radius-1);
            if(curSum == ansSum) ansCnt++;
            else if(curSum > ansSum) {
                ansSum = curSum;
                ansCnt = 1;
            }
        }
    }
    cout << ansCnt << " " << ansSum << endl;
    return 0;
}