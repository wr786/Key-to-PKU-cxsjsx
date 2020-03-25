#include<iostream>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;

multimap<int, int> mp; // power->id

int main() {
//    freopen("../in.txt", "r", stdin);
//    freopen("../out.txt", "w", stdout);
    mp.insert(pair<int, int>(1000000000, 1));
    int _t; scanf("%d", &_t);
    while(_t--) {
        int cur_id, cur_power;
        scanf("%d%d", &cur_id, &cur_power);
        mp.insert(pair<int, int>(cur_power, cur_id));
        auto it_left = mp.lower_bound(cur_power);
        auto it_right = mp.upper_bound(cur_power);
        if (it_left == mp.begin()) {
            printf("%d %d\n", cur_id, it_right->second);
        } else {
            it_left--;
            if (it_right == mp.end()) {
                printf("%d %d\n", cur_id, it_left->second);
            } else {
                if (cur_power - it_left->first > it_right->first - cur_power) {
                    printf("%d %d\n", cur_id, it_right->second);
                } else {
                    printf("%d %d\n", cur_id, it_left->second);
                }
            }
        }
    }
    return 0;
}