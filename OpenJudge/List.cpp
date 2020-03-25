#include <vector>
// 虽然说是list，但我没必要就用list（
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <cassert>
using namespace std;
typedef unordered_map<int, vector<int>> MAP;

int main() {
    MAP mp;
    int _t; cin >> _t;
    while(_t--) {
        string op;
        cin >> op;
        if(op == "new") {
            int id; cin >> id;
            mp[id] = vector<int>();
        } else if(op == "add") {
            int id, num; cin >> id >> num;
            mp[id].push_back(num);
        } else if(op == "merge") {
            int id1, id2; cin >> id1 >> id2;
            if(id1 != id2) {
                for(auto it=mp[id2].begin(); it!=mp[id2].end(); ++it) {
                    mp[id1].push_back(*it);
                }
                mp[id2].clear();
            }
        } else if(op == "unique") {
            int id; cin >> id;
            sort(mp[id].begin(), mp[id].end());
            auto it = unique(mp[id].begin(), mp[id].end());
            mp[id].erase(it, mp[id].end());
        } else if(op == "out") {
            int id; cin >> id;
            sort(mp[id].begin(), mp[id].end());
            for(auto it=mp[id].begin(); it!=mp[id].end(); ++it) {
                cout << *it << " ";
            }
            cout << endl;
        } else {
            assert("ERROR!" == "");
        }
    }
    return 0;
}
