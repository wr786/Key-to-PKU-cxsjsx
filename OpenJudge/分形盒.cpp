#include<string>
#include<iostream>
#include<cmath>
using namespace std;

int a[730][730];

inline void init(int x) {
    x--;
    for(int i=0; i<=pow(3,x); i++)
        for(int j=0; j<=pow(3,x); j++)
            a[i][j] = 0;
}

void generate(int num, int posx, int posy) {
    // pos => 左上角
    if(num == 1) {a[posx][posy] = 1; return;}
    int span = pow(3, num-2);
    generate(num-1, posx, posy);
    generate(num-1, posx + 2*span, posy);
    generate(num-1, posx+span, posy+span);
    generate(num-1, posx, posy + 2 * span);
    generate(num-1, posx+2*span, posy+2*span);
}

inline void output(int x) {
    x--;
    for(int i=0; i<pow(3,x); i++) {
        for(int j=0; j<pow(3,x); j++)
            cout << (a[i][j]?"X":" ");
        cout << endl;
    }
    cout << "-\n";
}

int main() {
    int x;
    while(cin >> x, x!=-1) {
        init(x);
        generate(x, 0, 0);
        output(x);
    }
    return 0;
}