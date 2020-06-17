#include <iostream>
using namespace std;
long long f[51];

int main() {
    f[0] = 1; f[1] = 1; f[2] = 1;
    for(int i=3; i<=50; i++)
        f[i] = f[i-1] + f[i-2];
    int n; cin >> n;
    while(n--) {
        int a, b; cin >> a >> b;
        cout << f[b-a+1] << endl;
    }
}