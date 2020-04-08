#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
#define INDENT "|     "

void tree(int depth=0, string folder="ROOT") {
    string type;
    vector<string> files;
    for(int i=0; i<depth; i++) cout << INDENT;
    cout << folder << endl;
    while(cin >> type) {
        if(type == "]" || type == "*") break;
        if(type[0] == 'f') files.push_back(type);
        else if(type[0] == 'd') tree(depth+1, type);
    }
    sort(files.begin(), files.end());
    for(auto it=files.begin(); it!=files.end(); ++it) {
        for(int i=0; i<depth; i++)
            cout << INDENT;
        cout << *it << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int _t = 0;
    while(true) {
        cout << "DATA SET " << ++_t << ":\n";
        tree();
        char tmp; cin >> tmp;
        if(tmp == '#') break;
        cin.putback(tmp);
        cout << "\n";
    }
    return 0;
}
