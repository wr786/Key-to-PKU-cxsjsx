#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<unordered_map>
#include<algorithm>
using namespace std;

int calc_factor(int n) {
    int ret = 0, t = n;
    for(int i=2; i<=t/2; i++) {
        if(n % i == 0) {
            ret++;
            while(n % i == 0) n /= i;
        }
    }
    return ret;
}

class NUM {
public:
    int val;
    int factor;
    NUM(int v, int f): val(v), factor(f) {}
};

class LessNUM {
public:
    bool operator () (const NUM& A, const NUM& B) {
        if(A.factor != B.factor) return A.factor > B.factor;
        else return A.val > B.val;
    }
};

class GreaterNUM {
public:
    bool operator () (const NUM& A, const NUM& B) {
        if(A.factor != B.factor) return A.factor < B.factor;
        else return A.val < B.val;
    }
};

int main() {
    priority_queue<NUM, vector<NUM>, LessNUM> lpq;
    priority_queue<NUM, vector<NUM>, GreaterNUM> gpq;
    int num; scanf("%d", &num);
    while(num--) {
        for(int i=0; i<10; i++) {
            int tmp; scanf("%d", &tmp);
            int fval = calc_factor(tmp);
            lpq.push(NUM(tmp, fval));
            gpq.push(NUM(tmp, fval));
        }
        printf("%d %d\n", gpq.top(), lpq.top());
        lpq.pop(); gpq.pop();
    }
}