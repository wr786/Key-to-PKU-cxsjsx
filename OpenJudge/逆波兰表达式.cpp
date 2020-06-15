#include<string>
#include<iostream>
#include<cstdio>
using namespace std;

double readIn() {
    string str;
    cin >> str;
    if(str == "*") return readIn() * readIn();
    if(str == "+") return readIn() + readIn();
    if(str == "-") return readIn() - readIn();
    if(str == "/") return readIn() / readIn();
    else return atof(str.c_str());
}

int main() {
    printf("%f\n", readIn());
    return 0;
}