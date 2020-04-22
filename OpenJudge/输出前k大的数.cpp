#include <queue>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

priority_queue<int, vector<int>, less<int> > heap;

int main() {
    int n; scanf("%d", &n);
    int tmp; 
    for(int i=0; i<n; i++) {
        scanf("%d", &tmp);
        heap.push(tmp);
    }
    int k; scanf("%d", &k);
    for(int i=0; i<k; i++) {
        printf("%d\n", heap.top());
        heap.pop();
    }
    return 0;
}