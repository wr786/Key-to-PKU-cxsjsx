#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
int honey;
int peach[101], cost[101];
int presumPeach[101], presumCost[101];
int ans;
int idx;

int main() {
    while(cin >> honey, honey != -1) {
        idx = 0; ans = 0;
        int tmpa, tmpb;
        while(cin >> tmpa >> tmpb, tmpa != -1 && tmpb != -1) {
            peach[++idx] = tmpa;
            cost[idx] = tmpb;
        }
        memset(presumPeach, 0, sizeof(presumPeach));
        memset(presumCost, 0, sizeof(presumCost));
        for(int i=1; i<=idx; i++)
            presumPeach[i] = presumPeach[i-1] + peach[i],
            presumCost[i] = presumCost[i-1] + cost[i];
        for(int i=1; i<=idx; i++)
            for(int j=i; j<=idx; j++) {
                if(presumCost[j] - presumCost[i-1] <= honey) {
                    ans = max(ans, presumPeach[j] - presumPeach[i-1]);
                }
            }
        cout << ans << endl;
    }
}