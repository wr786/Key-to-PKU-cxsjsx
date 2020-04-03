#include <iostream>
#include <string>
using namespace std;
#define INT_MAX 2147483647
int a[4][4];
int ans = INT_MAX;
string min_way;

inline void inc(int x, int y) {
    a[x][y] = (a[x][y] + 1) % 4;
}
inline void do_op_str(const string& str) {
    int l = str.length();
    for(int i=0; i<l; i++) {
        const char& c = str[i];
        switch(c) {
            case 'A': inc(1, 1); break;
            case 'B': inc(1, 2); break;
            case 'C': inc(1, 3); break;
            case 'D': inc(2, 1); break;
            case 'E': inc(2, 2); break;
            case 'F': inc(2, 3); break;
            case 'G': inc(3, 1); break;
            case 'H': inc(3, 2); break;
            case 'I': inc(3, 3); break;
            default: cout << "[ERROR] 1" << endl; break;
        }
    }
}
inline void manipulate(int op) {
    switch (op) {
        case 1: do_op_str("ABDE"); break;
        case 2: do_op_str("ABC"); break;
        case 3: do_op_str("BCEF"); break;
        case 4: do_op_str("ADG"); break;
        case 5: do_op_str("BDEFH"); break;
        case 6: do_op_str("CFI"); break;
        case 7: do_op_str("DEGH"); break;
        case 8: do_op_str("GHI"); break;
        case 9: do_op_str("EFHI"); break;
        default: cout << "[ERROR] 2" << endl; break;
    }
}
inline bool check() {
    for(int i=1; i<=3; i++)
        for(int j=1; j<=3; j++)
            if(a[i][j]) return false;
    return true;
}

void dfs(int depth, string rec, int last_op, int combo) {
    if(depth >= ans) return;
    if(check()) {
        if(depth < ans) {
            ans = depth;
            min_way = rec;
        }
        return;
    }
    if(combo == 4) return;
    for(int i=last_op; i<=9; i++) {
        manipulate(i);
        dfs(depth+1, rec + to_string(i), i, i==last_op?combo+1:1);
        manipulate(i);manipulate(i);manipulate(i); // 回转
    }
}

int main() {
    for(int i=1; i<=3; i++)
        for(int j=1; j<=3; j++)
            scanf("%d", &a[i][j]);
    dfs(0, "", 1, 0);
    int l = min_way.length();
    for(int i=0; i<l; i++) {
        if(i) printf(" ");
        printf("%c", min_way[i]);
    }
}