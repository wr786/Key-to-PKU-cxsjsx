#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int n;

inline bool isPlind(const string& s) {
    int l = s.length();
    for(int i=0; i<l/2; i++) {
        if(s[i] != s[l-1-i])
            return false;
    }
    return true;
}

int main() {
    cin >> n;
    for(int i=1; i<=n; i++) {
        string s; cin >> s;
        int l = s.length();
        bool flag = false;
        for(int span=l; span; span--) {
            for(int i=0; i<=l-span; i++) {
                string tmp = s.substr(i, span);
                if(isPlind(tmp)) {
                    cout << tmp << endl;
                    flag = true;
                    break;
                }
            }
            if(flag) break;
        }
    }
}