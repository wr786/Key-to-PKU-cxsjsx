#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main() {
    string str; cin >> str;
    vector<int> v;
    for(auto& ch: str) v.push_back(ch);
    do {
        for(auto& item: v) cout << (char)item;
        cout << endl;
    } while(next_permutation(v.begin(), v.end()));
    return 0;
}