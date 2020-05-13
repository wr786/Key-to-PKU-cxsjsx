#include <iostream>
using namespace std;
int f[20], sum[20];

int main() {
	int a, n, m, x; cin >> a >> n >> m >> x;
	if(x == 3) {
		cout << 2*a << endl;
		return 0;
	} // x >= 4
	f[1] = f[2] = 1;
	for(int i=3; i<=n; i++)
		f[i] = f[i-1] + f[i-2];
	for(int i=1; i<=n; i++)
		sum[i] = sum[i-1] + f[i];
	int _x = (m - (f[n-3]+1) * a) / sum[n-4];
	cout << (f[x-2]+1)*a + sum[x-3]*_x << endl;
	return 0;
}