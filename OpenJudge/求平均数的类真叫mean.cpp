#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
class CMean {
// 在此处补充你的代码
public:
	int sum;
	int cnt;
	int& target;
	CMean(int & t): target(t) {sum=0;cnt=0;}
	void operator () (int x) {
		sum += x;
		cnt ++;
		target = sum / (double)cnt;
	}
};

int main(int argc, char* argv[]) {
	int  v;
	int t;
	cin >> t;
	while ( t -- ) {
		cin >> v;
		vector<int> vec;
		while (v) {
			vec.push_back(v);
			cin >> v;
		}
		int myAver = 0;
		for_each(vec.begin(), vec.end(), CMean(myAver));
		cout << myAver << endl;
	}
	return 0;
}