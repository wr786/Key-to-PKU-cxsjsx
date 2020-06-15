#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;
#define LIM 1000000
int na[LIM], nb[LIM], nc[2*LIM];

inline string Mul(string a, string b) {
    // 默认la >= lb
    int la = a.length(), lb = b.length();
    for(int i=0; i<la; i++)
        na[i] = a[la-1-i] - '0';
    for(int i=0; i<lb; i++)
        nb[i] = b[lb-1-i] - '0';
    for(int i=0; i<la+lb; i++) {
        nc[i] = 0;
    }
    for(int i=0; i<la; i++)
        for(int j=0; j<lb; j++) {
            nc[i+j] += na[i] * nb[j];
        }
    string ret;
    for(int i=0; i<la+lb; i++) {
        ret = (char)(nc[i]%10 + '0') + ret;
        nc[i+1] += nc[i] / 10;
        nc[i] %= 10;
    }
    int cur = la + lb;
    while(nc[cur]) {
        ret = (char)(nc[cur]%10 + '0') + ret;
        nc[cur+1] += nc[cur] / 10;
        nc[cur++] %= 10;
    }
    // while(ret.length() > 1 && ret[0] == 0) ret = ret.substr(1);
//    cout << ret.substr(0, 500) << endl;
    return ret.substr(max((int)ret.length() - 500, 0), 500);
}

inline string Minus_1(const string& str) {
    string ret = str;
    int l = str.length();
    ret[l-1] -= 1;
    int curPos = l-1;
    while(ret[curPos] - '0' < 0) {
        ret[curPos] += 10;
        ret[--curPos] -= 1;
    }
    return ret;
}

string power_cal(string base, int e) {
    // 快速幂
    if(e == 0) return "1";
    if(e == 1) return base;
    if(e == 2) return Mul(base, base);
    int half = e / 2;
    string halfAns = power_cal(base, e / 2);
    string ret = Mul(halfAns, halfAns);
    if(e % 2) ret = Mul(ret, base);
    return ret;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int p; cin >> p;
    string ans = power_cal("2", p);
    ans = Minus_1(ans);
    int l = ans.length();
    cout << (int)(p * log(2) / log(10)) + 1 << endl;
    if(l < 500) {
        int makeup = 500 - l;
        while(makeup--) ans = "0" + ans;
        l = ans.length();
    }
    for(int i=l-500; i<l; i+=50) {
        cout << ans.substr(i, 50) << endl;
    }
}