#include <iostream>
#include <string>
using namespace std;
// 等价于将密码重置为target
int cur, target, l;
int tmp;
int ans = -1;

inline int bin_atoi(const string& str) {
    int ret = 0;
    for(int i=0; i<l; i++)
        if(str[i] == '1') ret += (1<<(l-1-i));
    return ret;
}

inline void flip(int& byte, int pos) {
    byte ^= (1 << pos);
}

inline bool getBit(const int& byte, int pos) {
   return byte & (1 << pos);
}

int main() {
    string c_str, t_str; cin >> c_str >> t_str;
    l = c_str.length();
    cur = bin_atoi(c_str), target = bin_atoi(t_str);
    for(int t=0; t<=1; t++) { // 枚举最后一位开关状态
        int switches = t;
        tmp = cur;
        int cnt = 0;
        for(int i=0; i<l; i++) {
            if(switches) {
                cnt++;
                flip(tmp, i);
                if(i) flip(tmp, i-1);
                if(i<l-1) flip(tmp, i+1);
            }
            switches = getBit(tmp, i) == getBit(target, i)? 0: 1;
        }
        if(tmp == target) {
            if(ans == -1) ans = cnt;
            else ans = min(ans, cnt);
        }
    }
    if(ans == -1) cout << "impossible\n";
    else cout << ans << endl;
    return 0;
}