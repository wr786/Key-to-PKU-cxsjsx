#include <iostream>
#include <cstring>
using namespace std;
template <int bitNum>
struct MyBitset
{
    char a[bitNum/8+1];
    MyBitset() { memset(a,0,sizeof(a));};
    void Set(int i,int v) {
        char & c = a[i/8];
        int bp = i % 8;
        if( v )
            c |= (1 << bp);
        else
            c &= ~(1 << bp);
    }
// 在此处补充你的代码
    bool bc_inited = false;
    class bit_container {
    private:
        bool bit;
    public:
        bit_container(bool _b=0): bit(_b) {}
        bit_container& operator = (const bit_container& other) {
            if(&other == this) return *this;
            bit = other.bit;
            return *this;
        }
        friend ostream& operator << (ostream& os, const bit_container& b) {
            os << b.bit;
            return os;
        }
    } bs[bitNum + 1];
    bit_container& operator [] (int idx) {
        if(!bc_inited) {
            for(int i=0; i<bitNum; i++) {
                bs[i] = (a[i/8] >> (i%8)) & 1;
            }
            bc_inited = true;
        }
        return bs[idx];
    }
////////////////////
    void Print() {
        for(int i = 0;i < bitNum; ++i)
            cout << (*this) [i];
        cout << endl;
    }

};

int main()
{
    int n;
    int i,j,k,v;
    while( cin >>  n) {
        MyBitset<20> bs;
        for(int i = 0;i < n; ++i) {
            int t;
            cin >> t;
            bs.Set(t,1);
        }
        bs.Print();
        cin >> i >> j >> k >> v;
        bs[k] = v;
        bs[i] = bs[j] = bs[k];
        bs.Print();
        cin >> i >> j >> k >> v;
        bs[k] = v;
        (bs[i] = bs[j]) = bs[k];
        bs.Print();
    }
    return 0;
}