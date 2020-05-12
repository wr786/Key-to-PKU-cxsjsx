#include <iostream>
#include <string>
using namespace std;
string dec2bin(int x){
// 在此处补充你的代码
	string  ret = "";
	for(int i=0; i<31; i++) {
		ret = to_string(x & 1) + ret;
		x >>= 1;
	}
	return ret;
}
int main(){
	int n;
	cin >> n;
	while(n--) {
		int x;
		cin >> x;
		cout << dec2bin(x) << endl;
	}
	return 0;
}