#include <iostream>
#include <algorithm>
using namespace std;
int s;
int income[16], cost[16];

int main() {
    int ans = 0;
    cin >> s;
    for(int i=0; i<15; i++)
        cin >> income[i] >> cost[i];
    for(int plan=0; plan<(1<<15); plan++) {
        // 枚举就vans了
        int pre=0, aft=0;
        for(int i=10; i<15; i++)
            if(plan & (1<<i))
                aft++;
        for(int i=0; i<10; i++)
            if(plan & (1<<i))
                pre++;
        if(pre > aft) continue; // 不够拖延
        int wage=0, costTime=0;
        for(int i=0; i<15; i++)
            if(plan & (1<<i))
                wage += income[i],
                costTime += cost[i];
        if(costTime <= s)
            ans = max(ans, wage);
    }
    cout << ans << endl;
}