#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

string fn(int x) {
    string ret;
    if(x == 0) {return "0";}
    for(int i=0; x; i++) {
        if(x & (1<<i)) {
            if(ret != "") ret = "+" + ret;
            if(i == 1) ret = "2" + ret;
            else ret = "2(" + fn(i) + ")" + ret;
            x &= ~(1<<i);
        }
    }
    return ret;
}

int main() {
    int n; cin >> n;
    cout << fn(n) << endl;
    return 0;
}