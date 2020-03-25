#include<iostream>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;

multimap<int, int> mp; // power->id

int main() {
    mp.insert(pair<int, int>(100000, 1));
    int _t; scanf("%d", &_t);
    while(_t--) {
        int cur_id, cur_power; scanf("%d%d", &cur_id, &cur_power);
        mp.insert(pair<int, int>(cur_power, cur_id));
        auto it_left = mp.lower_bound(cur_power);
        auto it_right = mp.upper_bound(cur_power);
        it_right--;
        int left_max = -1, right_min = -1;
        auto id_left = mp.end(), id_right = mp.end();
        if(it_left != it_right) { // 存在实力相同的人
            it_right++;
            auto id_ans = mp.end();
            for(auto it_tmp = it_left; it_tmp != it_right; it_tmp++) {
                if(it_tmp->second == cur_id) continue;
                if(id_ans == mp.end() || it_tmp->second < id_ans->second)
                    id_ans = it_tmp;
            }
            printf("%d %d\n", cur_id, id_ans->second);
        } else { // 不存在实力相同的人
            while (it_left != mp.begin()) {
                it_left--;
                if (it_left->first != left_max && left_max != -1)
                    break;
                if (left_max == -1) {
                    left_max = it_left->first;
                    id_left = it_left;
                } else if (it_left->second < id_left->second) {
                    id_left = it_left;
                }
            }
            it_right++;
            while(it_right != mp.end()) {
                if(it_right->first != right_min && right_min != -1)
                    break;
                if(right_min == -1) {
                    right_min = it_right->first;
                    id_right = it_right;
                } else if(it_right->second < id_right->second) {
                    id_right = it_right;
                }
                it_right++;
            }
            if(cur_power - left_max < right_min - cur_power && id_left != mp.end()) {
                printf("%d %d\n", cur_id, id_left->second);
            } else if(cur_power - left_max > right_min - cur_power && id_right != mp.end()) {
                printf("%d %d\n", cur_id, id_right->second);
            } else {
                if (id_right == mp.end())
                    printf("%d %d\n", cur_id, id_left->second);
                else if(id_left == mp.end())
                    printf("%d %d\n", cur_id, id_right->second);
                else if(id_left->second < id_right->second)
                    printf("%d %d\n", cur_id, id_left->second);
                else
                    printf("%d %d\n", cur_id, id_right->second);
            }
        }
    }
    return 0;
}