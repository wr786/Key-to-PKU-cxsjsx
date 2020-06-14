#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;
int n, k;
double wires[10001];

inline bool check(int perLength) {
    int sum = 0;
    for(int i=1; i<=n; i++) {
        sum += wires[i] / perLength;
        if(sum >= k) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k;
    for(int i=1; i<=n ;i++) {
        double tmp; cin >> tmp;
        wires[i] = 100.0*tmp;
    }
    sort(wires+1, wires+1+n);
    int l = 1, r = wires[n];
    while(l <= r) {
        int mid = (l+r)/2;
        if(check(mid)) {
            l = mid+1;
        } else {
            r = mid-1;
        }
    }
    cout << fixed << setprecision(2) << r/100.0 << endl;
    return 0;
}