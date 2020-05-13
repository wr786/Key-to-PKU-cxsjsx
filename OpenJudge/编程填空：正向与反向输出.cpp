#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;
class C1{
// 在此处补充你的代码
public:
	int* data;
	int size;
	C1(int sz, vector<int>& v) {
		data = new int[sz];
		size = sz;
		for(int i=0; i<sz; i++) data[i] = v[i];
	}
	int* operator * () {return data;}
	int& operator [] (int idx) {return data[size-1-idx];}
};

int main()
{
    vector<int> v;
    int p;
    int size;
    int k;
    cin >> k;
    while(k--){
        cin >> size;
        v.clear();
        for(int i = 0; i < size; ++i){
            cin >> p;
            v.push_back(p);
        }
        C1 o1 = C1(size,v);
        ostream_iterator<int> it(cout,"---");
        copy(*o1, (*o1)+size, it);
        cout<<endl;
        for(int i = 0; i < size; ++i){
            o1[i]*=2;
            cout<<o1[i]<<"***";
        }
        cout<<endl;
    }
    
}