#include<iostream>
using namespace std;

int main() {
	int a, b, i, j; cin>>a>>b>>i>>j;
	b >>= i;
	b &= (1 << (j-i+1)) - 1;
	b ^= (1 << (j-i+1)) - 1;
	b <<= i;
	int ret = ((((a>>(j+1))<<(j+1)) | b)) | (a &((1<<(i))-1)) ;
	cout << ret << endl;
	return 0;
}