#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
template <class T>
class CArray3D
{
// 在此处补充你的代码
private:
    class CArray2D {
    private:
        T* ls;
        int x_len;
        int y_len;
    public:
        CArray2D():x_len(0), y_len(0) {ls = nullptr;}
        CArray2D(int x, int y):x_len(x),y_len(y) {
            ls = new T[x*y];
        }
        T* operator [] (int idx) {
            return ls + idx*y_len;
        }
        operator T* () {
            return ls;
        }
        friend class CArray3D;
    } lst[5];
    int x_len;
    int y_len;
    int z_len;
public:
    CArray3D(int l, int m, int n):x_len(l), y_len(m), z_len(n) {
        for(int i=0; i<l; i++)
            lst[i] = CArray2D(m, n);
    }
    CArray2D& operator [] (int idx) {
        return lst[idx];
    }
};

CArray3D<int> a(3,4,5);
CArray3D<double> b(3,2,2);
void PrintA()
{
    for(int i = 0;i < 3; ++i) {
        cout << "layer " << i << ":" << endl;
        for(int j = 0; j < 4; ++j) {
            for(int k = 0; k < 5; ++k)
                cout << a[i][j][k] << "," ;
            cout << endl;
        }
    }
}
void PrintB()
{
    for(int i = 0;i < 3; ++i) {
        cout << "layer " << i << ":" << endl;
        for(int j = 0; j < 2; ++j) {
            for(int k = 0; k < 2; ++k)
                cout << b[i][j][k] << "," ;
            cout << endl;
        }
    }
}

int main()
{

    int No = 0;
    for( int i = 0; i < 3; ++ i ) {
        a[i];
        for( int j = 0; j < 4; ++j ) {
            a[j][i];
            for( int k = 0; k < 5; ++k )
                a[i][j][k] = No ++;
            a[j][i][i];
        }
    }
    PrintA();
    memset(a[1],-1 ,20*sizeof(int));
    memset(a[1],-1 ,20*sizeof(int));
    PrintA();
    memset(a[1][1],0 ,5*sizeof(int));
    PrintA();

    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 2; ++j )
            for( int k = 0; k < 2; ++k )
                b[i][j][k] = 10.0/(i+j+k+1);
    PrintB();
    int n = a[0][1][2];
    double f = b[0][1][1];
    cout << "****" << endl;
    cout << n << "," << f << endl;

    return 0;
}