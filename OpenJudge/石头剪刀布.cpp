#include <iostream>
#include <vector>
using namespace std;
vector<int> a, b;

int main() {
    int turn; cin >> turn;
    int periodA, periodB; cin >> periodA >> periodB;
    for(int i=0; i<periodA; i++) {
        int tmp; cin >> tmp;
        a.push_back(tmp);
    }
    for(int i=0; i<periodB; i++) {
        int tmp; cin >> tmp;
        b.push_back(tmp);
    }
    int cnt = 0;
    for(int i=0; i<turn; i++) {
        int handA = a[i%periodA], handB = b[i%periodB];
        if(handA == 2) {
            if(handB == 5) cnt++;
            if(handB == 0) cnt--;
        } else if(handA == 5) {
            if(handB == 0) cnt++;
            if(handB == 2) cnt--;
        } else {
            if(handB == 2) cnt++;
            if(handB == 5) cnt--;
        }
    }
    if(cnt == 0) cout << "draw";
    else if(cnt > 0) cout << "A";
    else cout << "B";
}