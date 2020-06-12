#include<iostream>

int fn(int cur, int tot) {
    if(cur == 1) return tot+1;
    return fn(cur-1, tot)*(tot)/(tot-1) + 1;
}

int main() {
    int n; std::cin >> n;
    for(int lastPile=1; ; lastPile++) {
        int curPile = lastPile*n + 1;
        bool flag = true;
        for(int i=n; i>=2; i--) {
            if(curPile % (n-1)) {
                flag = false;
                break;
            }
            curPile = curPile/(n-1)*n + 1;  // 注意顺序，防止溢出
        }
        if(flag) {
            std::cout << curPile << std::endl;
            return 0;
        }
    }
}