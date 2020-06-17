#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
char billboard[5][5];
int counter[5];
int tmp[5];

struct Node {
    int x;
    int y;

    Node(int _x = 0, int _y = 0) : x(_x), y(_y) {}
} undef[7];

int idx;

int main() {
    int t;
    cin >> t;
    while (t--) {
        memset(counter, 0, sizeof(counter));
        idx = 0;
        for (int i = 1; i <= 4; i++)
            for (int j = 1; j <= 4; j++) {
                cin >> billboard[i][j];
            }
        for (int i = 1; i <= 4; i++)
            for (int j = 1; j < i; j++) {    // 只要考虑一边，毕竟是对称的
                if (billboard[i][j] == 'W')
                    counter[i]++;
                else if (billboard[i][j] == 'L')
                    counter[j]++;
                else if (billboard[i][j] == '?') {
                    undef[++idx] = Node(i, j);
                }
            }
        int ans = 4;
        for (int i = 0; i < (1 << idx); i++) {
            memcpy(tmp, counter, sizeof(counter));
            for (int j = 0; j < idx; j++) {
                if (i & (1 << j)) tmp[undef[j + 1].x]++;
                else tmp[undef[j + 1].y]++;
            }
            int rank = 1;
            for (int i = 2; i <= 4; i++)
                if (tmp[i] > tmp[1]) rank++;
            ans = min(ans, rank);
        }
        cout << ans << endl;
    }
}