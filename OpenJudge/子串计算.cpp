#include <iostream>
#include <string>
#include <map>

using namespace std;
map<string, int> cnt;

int main() {
    string s;
    cin >> s;
    int l = s.length();
    for (int i = 0; i < l; i++) {
        for (int span = 1; span <= l - i; span++)
            cnt[s.substr(i, span)]++;
    }
    for (auto &p: cnt) {
        if (p.second > 1)
            cout << p.first << " " << p.second << endl;
    }
    return 0;
}