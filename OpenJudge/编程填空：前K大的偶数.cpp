#include <algorithm>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <string>
#include <map>
#include <set>

using namespace std;
class MyQueue
{
// 在此处补充你的代码
public:
	int size;
	priority_queue<int, vector<int>, less<int> > pq;
	MyQueue(int t): size(t) {}
	friend istream& operator >> (istream& is, MyQueue& mq) {
		int tmp; is >> tmp;
		mq.pq.push(tmp);
		return is;
	}
	friend ostream& operator << (ostream& os, MyQueue& mq) {
		bool flag = false;
		for(int i=0; i<mq.size; i++) {
			int tmp = mq.pq.top();
			if(tmp % 2 == 0) {
				if(flag) os << " ";
				os << tmp;
				flag = true;
			} else {
				i--;
			}
			mq.pq.pop();
		}
		return os;
	}
};
int main()
{
	int t;
	cin >> t;
	while(t--) {
		int n, k;
		cin >> n >> k;
		MyQueue q(k);
		for (int i = 0; i < n; ++i)
			cin >> q;
		cout<<q;
		cout << endl;
	}
	return 0; 
}