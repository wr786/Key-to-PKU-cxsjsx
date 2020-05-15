#include<iostream>
#include <string>
#include<queue>
#include <algorithm>
#include<vector>
using namespace std;

class A {
public:
	int price;
	int num;
	A(int n, int p): num(n), price(p) {}
};

class cmp {
public:
	bool operator() (const A& a, const A& b) const {return a.price==b.price? a.num<b.num: a.price>b.price;}
};

priority_queue<A, vector<A>, cmp> pq;

int main() {
	int n;
	cin >> n;
	while(n--) {
		string op; cin >> op;
		if(op == "BUY") {
			int num; cin >> num;
			int cost =0;
			while(!pq.empty() && num!=0) {
				A tmp = pq.top();
				int buy =  min(num, tmp.num);
				cost += buy*tmp.price;
				num -= buy;
				if(buy == tmp.num) pq.pop();
				else {
					pq.pop();
					pq.push(A(tmp.num-buy, tmp.price));
				}
			}
			cost += 40*num;
			cout << cost << endl;
		} else {
			int n,p; cin >> n >> p;
			pq.push(A(n,p));
		}
	}
}