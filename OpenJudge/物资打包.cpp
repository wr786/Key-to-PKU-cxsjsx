#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <cctype>
#include <limits>
#include <cmath>
using namespace std;
const int INF = numeric_limits<int>::max();
int n, m;
int x;
int a[1001];

inline bool check(int x) {
    long long sum = 0;
    for(int i=1; i<=n; i++) {
        sum += ceil(a[i] / (double)x);
        if(sum > m) return false;
    }
    return true;
}

int main() {
    cin >> n >> m;
    for(int i=1; i<=n; i++)
        cin >> a[i];
    int l = 1, r = 10000010;
    int last = 0;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(mid == last) break;
        if(check(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
        last = mid;
    }
    cout << r << endl;
}