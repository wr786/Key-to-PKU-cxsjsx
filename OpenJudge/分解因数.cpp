#include<iostream>
#include<algorithm>
using namespace std;

int fn(int x, int lim) {
    if(x == 1) {
        return 1;   // 分解完毕
    }
    int ret = 0;
    for(int i=min(x,lim); i >= 2; i--) { // 按大小找，依次越来越小
        if(x % i == 0) {
            ret += fn(x/i, i);  
        }
    }
    return ret;
}

int main() {
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        cout << fn(n, n) << endl;
    }
    return 0;
}