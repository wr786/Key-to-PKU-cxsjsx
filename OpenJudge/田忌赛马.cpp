#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <cctype>
#include <limits>
using namespace std;
const int INF = numeric_limits<int>::max();
int n, x;
int a[10];
vector<int> myhorses;

int main() {
    cin >> n >> x;
    for(int i=1; i<=n; i++) {
        cin >> a[i];
        myhorses.push_back(i);
    }
    do {
        int cnt = 0;
        for(int i=1; i<=n; i++){
            if(myhorses[i-1] - a[i] >= x)
                cnt++;
            else
                cnt--;
        }
        if(cnt > 0) {
            bool out = false;
            for(auto& item: myhorses) {
                if(out) cout << " ";
                cout << item;
                out = true;
            }
            cout << endl;
        }
    } while(next_permutation(myhorses.begin(), myhorses.end()));
    return 0;
}