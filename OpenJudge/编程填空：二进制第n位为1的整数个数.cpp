#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
#include <functional>

auto Pred(int N) -> function<int(int)> {
	return [=](int x){
		for(int i=1; i<=N; i++)
			x = x >> 1;
		return x & 1;
	};
}

template<typename IT>
int count_if(IT begin, IT end, int(*fun)(int)) {
	int ret = 0;
	for(IT it=begin; it!=end; it++)
		ret += fun(*it);
	return ret;	
}


int main(int argc, char** argv) {	
	int n, x;
	vector<int> intVec;
	cin>>n>>x; 
	while(x) {
		intVec.push_back(x);
		cin>>x;
	}
	cout<<count_if(intVec.begin(), intVec.end(), Pred(n))<<endl;
	return 0;
}