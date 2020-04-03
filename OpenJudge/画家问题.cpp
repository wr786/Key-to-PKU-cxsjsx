#include <iostream>
using namespace std;
int n;
int a[16];
int b[16];
int ans = -1;

void setBit(int& target, int pos, bool st) {
    if(st) {
        target |= (1<<(n-1-pos));
    } else {
        target &= ~(1<<(n-1-pos));
    }
}

void duplicate(int _a[], int _b[]) {
    for(int i=0; i<n; i++)
        _b[i] = _a[i];
}

bool getBit(const int& byte, int pos) {
    return byte & (1<<pos);
}

void flipBit(int& byte, int pos) {
    byte ^= (1<<pos);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            char tmp; cin >> tmp;
            setBit(a[i], j, tmp=='w'); // 将白色设置为1，化归为关灯问题
        }
    }
    int switches = 0;
    for(int t=0; t<(1<<n); t++) { // 枚举第一行的状态
        int tmp_ans = 0;
        switches = t;
        duplicate(a, b); // 初始化
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                if(getBit(switches, n-1-j)) {
                    tmp_ans ++;
                    if(j>0) flipBit(b[i], n-j);
                    if(j<n-1) flipBit(b[i], n-j-2);
                    flipBit(b[i], n-j-1);
                    if(i < n-1) flipBit(b[i+1], n-j-1);
                }
            }
            switches = b[i];
            if(i == n-1) {
                if(b[i] == 0) {
                    if(ans == -1) ans = tmp_ans;
                    else ans = min(tmp_ans, ans);
                }
            }
        }
    }
    if(ans == -1) cout << "inf\n";
    else cout << ans << endl;
}