#include <iostream>
#include <string>
#include <stack>
using namespace std;
#define endl '\n'
bool flag[105];
string str;


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    while(cin.peek() != EOF) {
        getline(cin, str);
        cout << str << endl;
        int n = str.length();
        stack<int> s;
        fill(flag, flag+n, false);
        for(int i=0; i<n; i++) {
            if(str[i] == '(') s.push(i);
            else if(str[i] == ')') {
                if(!s.empty()) {
                    flag[s.top()] = flag[i] = true;
                    s.pop();
                }
            }
        }
        for(int i=0; i<n; i++) {
            if(!flag[i]) {
                if (str[i] == '(') cout << '$';
                else if (str[i] == ')') cout << '?';
                else cout << ' ';
            } else cout << ' ';
        }
        cout << endl;
    }
}