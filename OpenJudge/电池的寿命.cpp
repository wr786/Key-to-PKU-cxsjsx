#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    int n;
    while(cin >> n) {
        int minx = 0x3f3f3f3f, maxx = 0, sumx = 0;
        for(int i=0; i<n; i++) {
            int tmp; cin >> tmp;
            minx = min(minx, tmp);
            maxx = max(maxx, tmp);
            sumx += tmp;
        }
        if(n == 2) cout << fixed << setprecision(1) << 1.*minx << endl;
        else if(maxx > sumx - maxx) {
            cout << fixed << setprecision(1) << 1.*(sumx - maxx) << endl;
        } else {
            cout << fixed << setprecision(1) << sumx / 2.0 << endl;
        }
    }
    return 0;
}