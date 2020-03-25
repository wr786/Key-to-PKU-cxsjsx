#include<unordered_set>
#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;

int main() {
    int _t; cin >> _t;
    unordered_multiset<int> st;
    unordered_map<int, bool> visited;
    while(_t--) {
        string op; cin >> op;
        int val; cin >> val;
        if(op == "add") {
            st.insert(val);
            visited[val] = true;
            cout << st.count(val) << endl;
        } else if(op == "del") {
            cout << st.count(val) << endl;
            if(st.count(val)) st.erase(val);
        } else {
            cout << (visited[val]?1:0) << " " << st.count(val) << endl;
        }
    }
    return 0;
}