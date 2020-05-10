#include<iostream>
#include<unordered_map>
#include<queue>
#include<string>
#include<set>
using namespace std;

int main() {
	int _t; cin >> _t;
	while(_t--) {
		unordered_map<string, queue<string>> party;
		unordered_map<string, set<string>> computer;
		int N; cin >> N;
		while(N--) {
			char op; string trainer, pokemon; cin >> op >> trainer >> pokemon;
			if(op == 'C') {
				queue<string>& curParty = party[trainer];
				set<string>& curCmt = computer[trainer];
				if(curParty.size() == 6) {
					curCmt.insert(curParty.front());
					curParty.pop();
					curParty.push(pokemon);
				} else {
					curParty.push(pokemon);
				}
			} else if (op == 'T') {
				queue<string>& curParty = party[trainer];
				set<string>& curCmt = computer[trainer];
				if(curCmt.count(pokemon)) {
					cout << "Success\n";
					curCmt.erase(pokemon);
					curParty.push(pokemon);
					if(curParty.size() == 7) {
						curCmt.insert(curParty.front());
						curParty.pop();
					}
				} else {
					cout << "Failed\n";
				}
			}
		}
	}
}