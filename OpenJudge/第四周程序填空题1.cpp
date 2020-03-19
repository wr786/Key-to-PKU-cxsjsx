#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
class Complex {
private:
    double r,i;
public:
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }
		Complex(): r(0), i(0) {}
		Complex(const char* cstr) {
			string str(cstr);
			int addPos = str.find("+");
			r = atoi(str.substr(0, addPos).c_str());
			i = atoi(str.substr(addPos+1, str.length() - addPos - 1).c_str());
		}
};
int main() {
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}
