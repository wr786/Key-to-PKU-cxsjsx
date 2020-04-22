#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
#define endl '\n'
int n;
long long a[100001];
long long b[100001];
long long ans;

void MergeAndGetInverse(int left, int mid, int right) {
    int p1 = left, p2 = mid+1, p3 = left;
    while(p1 <= mid && p2 <= right) {
        if(a[p1] > a[p2]) {
            // 逆序
            b[p3++] = a[p2++];
            ans += mid + 1 - p1;
        } else {
            b[p3++] = a[p1++];
        }
    }
    while(p1 <= mid) b[p3++] = a[p1++];
    while(p2 <= right) b[p3++] = a[p2++];
    for(int i=left; i<=right; i++) a[i] = b[i];
}

void Merge(int l, int r) {
    if(l < r) {
        int mid = (l + r) >> 1;
        Merge(l, mid);
        Merge(mid+1, r);
        MergeAndGetInverse(l, mid, r);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i=1; i<=n; i++)
        cin >> a[i];
    Merge(1,n);
    cout << ans;
    return 0;
}
