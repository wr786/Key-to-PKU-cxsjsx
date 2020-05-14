#include <iostream>
using namespace std;
// 在此处补充你的代码
template<typename T, typename Pred>
T sum(T* p, int size, Pred fn) {
	T ret = fn(p[0]);
	for(int i=1; i<size; i++)
		ret += fn(p[i]);
	return ret;
}

int sqr(int n) {
    return n * n;
}
int main() {
    int t, n, a[0x100];
    cin >> t;
    for (int c = 0; c < t; ++c) {
        cin >> n;
        for (int i = 0; i < n; ++i) cin >> a[i];
        cout << sum(a, n, sqr) << endl;
    }
    return 0;
}