#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
vector<int> array;
#define FLAG 1000000001

int main() {
    int n; cin >> n;
    array.push_back(-1);
    for(int i=0; i<n; i++) {
        int tmp; cin >> tmp;
        array.push_back(tmp);
    }
    array.push_back(FLAG);  // 虚数字，纯用作标记
    int m; cin >> m;
    while(m--) {
        int target; cin >> target;
        // 特判边缘
        if(target <= array[1]) {
            cout << array[1] << endl;
            continue;
        }
        if(target >= array[n]) {
            cout << array[n] << endl;
            continue;
        }
        auto it = lower_bound(array.begin(), array.end(), target);  // >=
        auto it2 = it--;
        if(abs(*it - target) <= abs(*it2 - target)) {
            cout << *it << endl;
        } else {
            cout << *it2 << endl;
        }
    }
}