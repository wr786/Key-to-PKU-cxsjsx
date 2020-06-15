#include<iostream>
#include<string>
using namespace std;

inline long long parse(int x, int base) {
    long long ret = 0;
    for(auto& ch: to_string(x)) {
        ret = ret * base + ch - '0';
    }
    return ret;
}

int main() {
    int p, q, r; cin >> p >> q >> r;
    int minBase = 0;
    for(auto& ch: to_string(p)) {
        minBase = max(minBase, ch - '0');
    }
    for(auto& ch: to_string(q)) {
        minBase = max(minBase, ch - '0');
    }
    for(auto& ch: to_string(r)) {
        minBase = max(minBase, ch - '0');
    }
    minBase++;
    for(int i=minBase; i<=1000; i++) {
        long long lhs = parse(p, i) * parse(q, i);
        long long rhs = parse(r, i);
        if(lhs == rhs) {
            cout << i << endl;
            return 0;
        }
    }
    cout << 0 << endl;
    return 0;
}