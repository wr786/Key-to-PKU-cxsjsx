#include <iostream>
#include <unordered_map>
using namespace std;
#define LIM 21252+365

enum Period {
    Phy = 23,
    Emo = 28,
    Int = 33,
};

unordered_map<int, int> counter;

int main() {
    int p, e, i, d; cin >> p >> e >> i >> d;
    while(p > Phy) p -= Phy;
    while(e > Emo) e -= Emo;
    while(i > Int) i -= Int;
    counter.clear();
    for(p; p<=LIM; p+=Phy) counter[p] += 1;
    for(e; e<=LIM; e+=Emo) counter[e] += 1;
    for(i; i<=LIM; i+=Int) {
        counter[i] += 1;
        if(counter[i] == 3) {
            if(i > d) {
                cout << i - d << endl;
                return 0;
            } else if(i == d) { // 下一次，下一次
                cout << 21252 << endl;
                return 0;
            }
        }
    }
}