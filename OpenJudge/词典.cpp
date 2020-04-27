#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
#define endl '\n'
unordered_map<string, string> dict;

int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	string tmp1, tmp2;
	while(cin >> tmp1 >> tmp2) {
		dict[tmp2] = tmp1;
		cin.ignore();
		if(cin.peek() == '\n') break;
	}
	while(cin >> tmp1) {
		if(dict[tmp1] == "") {
			cout << "eh" << endl;
		} else {
			cout << dict[tmp1] << endl;
		}
	}
	return 0;
}