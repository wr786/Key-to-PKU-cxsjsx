#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
template<typename T>
class Print {
public:
	int counter;
	Print(int c): counter(c) {}
	Print& operator + (T a) {
		cout << a;
		if(--counter == 0) cout << '\n';
		return *this;
	}
};
int main(){
	string s[20];
	int num[20];
	int m,n;
	
	while(cin >> m >> n){
		for(int i=0; i<m; i++){
			cin >> s[i];
		}
		accumulate(s, s+m, Print<string>(m));
		for(int i=0; i<n; i++){
			cin >> num[i];
		}
		accumulate(num, num+n, Print<int>(n));
	}
}