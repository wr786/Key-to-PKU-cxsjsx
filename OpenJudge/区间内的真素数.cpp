#include <iostream>
using namespace std;
#define LIM 1000001
bool vis[LIM];
bool isPrime[LIM];

inline void generatePrimes() {
    for(int i=2; i<LIM; i++) {
        if(!vis[i]) {
            isPrime[i] = true;
            for(int j=i; j<LIM; j+=i)
                vis[j] = true;
        }
    }
}

inline int getReverse(int x) {
    string num = to_string(x);
    int len = num.length(), ret = 0;
    for(int i=len-1; i>=0; i--)
        ret = ret*10 + num[i]-'0';
    return ret;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	generatePrimes();
	int m, n; cin >> m >> n;
	bool flag = false;
	for(int i=m; i<=n; i++) {
	    if(isPrime[i] && isPrime[getReverse(i)]) {
	        if(flag)
	            cout << ",";
            cout << i;
            flag = true;
	    }
	}
	if(!flag) cout << "No";
}