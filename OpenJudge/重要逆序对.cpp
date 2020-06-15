#include<iostream>
using namespace std;
int n;
int array[200001];
int tmp[200001];

long long merge(const int beg, const int end) {
    if(beg == end) {return 0ll;}
    long long ret = 0ll;
    int mid = (beg + end) / 2;
    ret += merge(beg, mid);
    ret += merge(mid+1, end);
    // 现在左边和右边理应是已经排好了的
    int l = beg, r = mid+1;
    while(r <= end) {
        while(l <= mid && array[l] <= 2 * array[r]) {
            l++;
        }
        ret += mid - l + 1;
        r++;
    }
    // 接下来进行排序
    int idx = beg;
    l = beg, r = mid+1;
    while(idx <= end) {
        if(l > mid) {
            tmp[idx++] = array[r++];
        } else if (r > end) {
            tmp[idx++] = array[l++];
        } else if (array[l] <= array[r]) {
            tmp[idx++] = array[l++];
        } else {
            tmp[idx++] = array[r++];
        }
    }
    for(int i=beg; i<=end; i++)
        array[i] = tmp[i];
    return ret;
}

int main() {
    cin >> n;
    for(int i=1; i<=n; i++)
        cin >> array[i];
    cout << merge(1, n) << endl;
    return 0;
}