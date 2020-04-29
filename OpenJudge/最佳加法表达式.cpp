#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;
#define endl '\n'
string INF = "78655445319000110296666666666666666666";
class CHugeInt {    // 直接把之前作业写的搬过来再稍加改动（
private:
    string str;
public:
    CHugeInt(const char* s):str(s) {}
    CHugeInt(const int& x):str(to_string(x)) {}
    CHugeInt(const string& s):str(s) {}
    CHugeInt(const CHugeInt& other):str(other.str) {}
    CHugeInt(): str("0") {}
    int length() {
        return str.length();
    }
    friend ostream& operator << (ostream& os, const CHugeInt& CHI) {
        os << CHI.str;
        return os;
    }
    CHugeInt operator + (const CHugeInt& other) {
        string a = this->str, b = other.str;
        int la = a.length(), lb = b.length();
        if(la < lb) {
            swap(la, lb);
            swap(a, b);
        } // la >= lb
        int updigit = 0;
        for(int i=1; i<=lb; i++) {
            int pa = la - i, pb = lb - i;
            a[pa] = a[pa] - '0' + b[pb] - '0' + updigit;
            updigit = a[pa] / 10;
            a[pa] %= 10;
            a[pa] += '0';
        }
        int cur = la - lb - 1;
        while(updigit && cur>= 0) {
            a[cur] = a[cur] - '0' + updigit;
            updigit = a[cur] / 10;
            a[cur] %= 10;
            a[cur] += '0';
            cur--;
        }
        if(updigit) {a = to_string(updigit) + a;}
        return CHugeInt(a);
    }
    CHugeInt operator + (const int& other) {
        return *this + CHugeInt(other);
    }
    friend CHugeInt operator + (const int& other, const CHugeInt& CHI) {
        return CHugeInt(other) + CHI;
    }
    void operator += (const int& other) {
        *this = *this + CHugeInt(other);
    }
    friend CHugeInt& operator ++ (CHugeInt& CHI) {
        CHI = CHI + 1;
        return CHI;
    }
    friend CHugeInt operator ++ (CHugeInt& CHI, int x) {
        CHugeInt tmp(CHI);
        CHI = CHI + 1;
        return tmp;
    }
    bool operator < (const CHugeInt& other) {
        return str < other.str;
    }
    int operator [] (int idx) {
        return str[idx] - '0';
    }
};
int m, l; string str;
CHugeInt dp[51][51]; // 几个加号,前几位

inline CHugeInt min(CHugeInt A, CHugeInt B) {
    int la = A.length(), lb = B.length();
    if(la < lb) return A;
    if(la > lb) return B;
    for(int i=0; i<la; i++) {
        if(A[i] > B[i])
            return B;
        if(A[i] < B[i])
            return A;
    }
    return A;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    while(cin >> m >> str) {
        l = str.length();
        for(int end=1; end<=l; end++) {
//            dp[0][end] = num[1][end];
            dp[0][end] = str.substr(0, end);
        }
        for(int plusNum=1; plusNum<=m; plusNum++)
            for(int end=1; end<=l; end++) {
                dp[plusNum][end] = INF;
                for(int div=1; div<end; div++) {
//                    dp[plusNum][end] = min(dp[plusNum][end], dp[plusNum-1][div] + num[div+1][end]);
                    dp[plusNum][end] = min(dp[plusNum][end], dp[plusNum-1][div] + str.substr(div, end-div));
                }
            }
        cout << dp[m][l] << endl;
    }
}
