#include <string>
#include <iostream>
#include <cstdio>
using namespace std;

inline bool readIn(string& str) {
    str = "";
    char c;
    while((c=getchar()) != EOF) {
        if(c == '\n') return true;
        if(c != ' ') str += c;
    }
    return false;
}

string parse(string str) {
    int l = str.length();
    if(str.find('(') != string::npos) {
        int lc = str.find('(');
        int lccnt = 1;
        for(int i=lc+1; i<l; i++) {
            if(str[i] == '(') lccnt++;
            else if(str[i] == ')') {
                lccnt--;
                if(lccnt == 0) {
                    string tmp = str.substr(0, lc) + parse(str.substr(lc+1, i-lc-1));
                    if(i+1 < l) tmp += str.substr(i+1);
                    return parse(tmp);
                }
            }
        }
    } else {
        if(str.find('!') != string::npos) {
            int pos = str.find('!');
            int rpos = pos+1;
            while(str[rpos] == '!') rpos++;             // 小 心 一 元 运 算 符
            char ret;
            if((rpos - pos) % 2) ret = str[rpos]=='V'?'F':'V';
            else ret = str[rpos];
            string tmp = str.substr(0,pos) + ret + str.substr(rpos+1);
            return parse(tmp);
        }
        if(str.find('&') != string::npos) {
            int pos = str.find('&');
            bool left = str[pos-1]=='V';
            bool right = str[pos+1]=='V';
            char ret = left && right? 'V':'F';
            string tmp = str.substr(0,pos-1) + ret;
            if(pos+2 < l) tmp += str.substr(pos+2);
            return parse(tmp);
        }
        if(str.find('|') != string::npos) {
            int pos = str.find('|');
            bool left = str[pos-1]=='V';
            bool right = str[pos+1]=='V';
            char ret = left || right? 'V':'F';
            string tmp = str.substr(0,pos-1) + ret;
            if(pos + 2 < l) tmp += str.substr(min(pos+2, l));
            return parse(tmp);
        }
        return str; // 一元情况
    }
    return "ERROR";
}

int main() {
    int _t = 0;
    string expression;
    bool flag = true;
    while(flag) { // 对应换行前的^Z
        // cout << expression << endl;
        flag = readIn(expression);
        _t++;
        if(expression != "") { // 对应换行后的^Z
            printf("Expression %d: ", _t);
            printf("%c\n", parse(expression)=="V"?'V':'F');
        }
    }
    return 0;
}