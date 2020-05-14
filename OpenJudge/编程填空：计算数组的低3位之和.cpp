#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
class CMy_add {
public:
	int& target;
	CMy_add(int& t): target(t) {}
	void operator() (int x) {target += x & 7;}
};

int main(int argc, char* argv[]) {
	int  v, my_sum=0;
	vector<int> vec;		
	cin>>v;
	while ( v ) {
		vec.push_back(v);
		cin>>v;
	}
	for_each(vec.begin(), vec.end(), CMy_add(my_sum));
	cout<<my_sum<<endl;	
	return 0;
}