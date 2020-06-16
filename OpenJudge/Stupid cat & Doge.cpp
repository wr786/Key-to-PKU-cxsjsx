#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

void rotate(long long blockID, int level, long long&x, long long & y) {
    long long tmpx = x, tmpy = y;
    long long span = pow(2, level); // 当前块的直径
    if(blockID == 1) {  // 左上角，沿↘对称
        x = tmpy;
        y = tmpx;
    } else if(blockID == 4) {   // 左下角，沿↙对称
        x = span - tmpy - 1;    // 用-是因为我们是从0开始标号的
        y = span - tmpx - 1;
    }
}

void findPos(int level, long long id, long long &x, long long &y) {
    if(level <= 0) return;
    long long span = pow(2, 2*(level-1));   // 四分之一块里的id数
    long long blockID = (id + span - 1) / span;    // 当前id所处的块的编号
    findPos(level - 1, id - (blockID-1) * span, x, y);
    rotate(blockID, level-1, x, y);
    span = pow(2, level - 1);   // 换成四分之一块的直径
    switch(blockID) {
        case 1:
            break;
        case 2:
            x += span;
            break;
        case 3:
            x += span;
            y += span;
            break;
        case 4:
            y += span;
            break;
        default:
            cout << "[ERROR]" << endl;
    }   // 增加偏移量
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        long long n, s, d;
        cin >> n >> s >> d;
        long long x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        findPos(n, s, x1, y1);
        findPos(n, d, x2, y2);
        cout << (long long)round(sqrt(pow(10.*(x1 - x2), 2) + pow(10.*(y1 - y2), 2))) << endl;
    }
}