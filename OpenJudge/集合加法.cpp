#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int _t; cin >> _t;
    for(int i=1; i<=_t; i++) {
        unordered_map<int, int> setA;
        int sizeA, sizeB, tmp, cnt=0, target;
        cin >> target >> sizeA;
        for(int i=0; i<sizeA; i++) {
            cin >> tmp;
            setA[tmp] += 1;
        }
        cin >> sizeB;
        for(int i=0; i<sizeB; i++) {
            cin >> tmp;
            cnt += setA[target - tmp];
        }
        cout << cnt << endl;
    }
}