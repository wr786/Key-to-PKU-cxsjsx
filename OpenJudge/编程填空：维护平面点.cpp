#include <set>
#include <iostream>
#include <string>
using namespace std;
// 在此处补充你的代码
class myComp {
public:
	bool operator () (const pair<int, int>& A, const pair<int, int>& B) const {
		if(A.first < 0 || B.first < 0) return A.second > B.second;
		return A.first < B.first;
	} 
};

int main() {
	string cmd;
	set<pair<int, int>, myComp> S;
	while (cin >> cmd) {
		if (cmd == "A") {
			int x, y;
			cin >> x >> y;
			S.insert(make_pair(x, y));
		} else if (cmd == "Qx") {
			int x;
			cin >> x;
			cout << S.lower_bound(make_pair(x, -1))->second << endl;
		} else if (cmd == "Qy") {
			int y;
			cin >> y;
			cout << S.lower_bound(make_pair(-1, y))->first << endl;
		} else {
			int x, y;
			cin >> x >> y;
			S.erase(make_pair(x, y));
		}
	}
	return 0;
}