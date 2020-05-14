#include <iostream>
using namespace std;

int main() {
	int t; cin >> t;
	while(t--) {
		int n, i, j; cin >> n >> i >> j;
		int ret = (1<<j) - (1<<(i+1)); // i~j间为1
		ret |= n & (1<<i);
		ret |= (~n) & (1<<j);
		cout << hex << ret << endl;
	}
	return 0;
}