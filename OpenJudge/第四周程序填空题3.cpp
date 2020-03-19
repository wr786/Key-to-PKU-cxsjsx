#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
// 在此处补充你的代码
private:
	int m;
	int n;
	int **p;
public:
	Array2() {
		m = n = 0;
		p = NULL;
	}
	Array2(int _m , int _n) {
		m = _m, n = _n;
		p = new int*[m];
		for(int i=0; i<m; i++)
			p[i] = new int[n];
	}
	int* operator [] (int x) {
		return p[x];
	}
	int operator () (int x, int y) {
		return p[x][y];
	}
	Array2(const Array2& other) {
		if(other.p) {
			m = other.m;
			n = other.n;
			delete []p;
			p = new int*[m];
			for(int i=0; i<m; i++) p[i] = new int[n];
			memcpy(p, other.p, sizeof(int)*m*n);
		} else {
			m = n = 0;
			p = NULL;
		}
	}
};

int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}
