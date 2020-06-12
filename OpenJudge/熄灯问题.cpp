#include <iostream>
using namespace std;
int a[10][10];
int b[10][10];
int ansRow;

inline bool getBit(const int& byte, int pos) {
    return byte & (1<<pos);
}

inline void reverse(int& tar) {
    tar = 1 - tar;
}

int ans[5];

int main() {
    for(int i=0; i<5; i++)
        for(int j=0; j<6; j++)
            cin >> a[i][j];
    for(int i=0; i<(1<<6); i++) {
        int curRow = i;
        for(int i=0; i<5; i++)
            for(int j=0; j<6; j++)
                b[i][j] = a[i][j];
        for(int row=0; row<5; row++) {
            for(int col=0; col<6; col++) {
                if(getBit(curRow, col)) {
                    reverse(b[row][col]);
                    if(col) reverse(b[row][col-1]);
                    if(col<5) reverse(b[row][col+1]);
                    if(row<4) reverse(b[row+1][col]);
                }
            }
            ans[row] = curRow;
            curRow = 0;
            for(int col=0; col<6; col++)
                if(b[row][col]) curRow |= (1<<col);
            if(row == 4 && curRow == 0) {
                // 所有的灯都熄灭了
                for(int r=0; r<5; r++) {
                    bool output_flag = false;
                    for(int c=0; c<6; c++) {
                        if(output_flag) cout << " ";
                        cout << getBit(ans[r], c);
                        output_flag = true;
                    }
                    cout << "\n";
                }
                return 0;
            }
        }
    }
}