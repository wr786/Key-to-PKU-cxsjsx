#include <iostream>
using namespace std;
#define endl '\n'

int gcd(int a, int b) {return b? gcd(b, a%b): a;}

class Fraction {
private:
    int numerator;
    int denominator;
public:
    Fraction(int _m=0, int _n=1) {
        int div = gcd(_m, _n);
        numerator = _m / div;
        denominator = _n / div;
    }
    bool operator < (const Fraction & other) {
        return (double)numerator/denominator < (double)other.numerator/other.denominator;
    }
    void print() {
        cout << numerator << " " << denominator << endl;
    }
};


int main() {
	ios::sync_with_stdio(false); cin.tie(0);
    int N, A, B; cin >> N >> A >> B;
    Fraction toCmp = Fraction(A, B);
    Fraction ans;
    for(int i=1; i<=N; i++)
        for(int j=0; j<i; j++) {
            if(!(Fraction(j, i) < toCmp)) break;
            if(ans < Fraction(j, i)) ans = Fraction(j, i);
        }
    ans.print();
    return 0;
};