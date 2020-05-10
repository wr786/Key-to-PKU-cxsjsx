#include <iostream>
#include <string>
#include <vector>
using namespace std;
template<typename IT, typename T, typename Pred>
IT FindFirstLess(IT begin, IT end, T target, Pred fun) {
	IT it;
	for(it=begin; it!=end; it++) {
		if(fun(*it , target)) break;
	}
	return it;
}
int main()
{
	int t;
	cin >> t;
	while(t--) {
		int n ;
		string type; 
		cin >> n >> type;
		vector<int> vi;
		vector<string> vs;
		if( type == "N") {
			int a,m;
			for(int i = 0;i < n  - 1; ++i) {
				
				cin >> a;
				vi.push_back(a);
			}
			cin >> m;
			vector<int>::iterator p = FindFirstLess(vi.begin(),vi.end(),m,less<int>());
			if( p!= vi.end())
				cout << * p << endl;
			else
				cout << "Not Found" << endl; 
				
		}
		else {
			string a,m;
			for(int i = 0;i < n - 1; ++i) {
				cin >> a;
				vs.push_back(a);
			}
			cin >> m;
			vector<string>::iterator p = FindFirstLess(vs.begin(),vs.end(),m,less<string>());
			if( p!= vs.end())
				cout << * p << endl;
			else
				cout << "Not Found" << endl; 
		
		}
	}
    return 0;
}