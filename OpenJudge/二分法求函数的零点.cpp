#include <cmath>
#include <cstdio>
#define eps 1e-6

inline double f(double x) {
    // x5 - 15 * x4+ 85 * x3- 225 * x2+ 274 * x - 121
    return pow(x, 5) - 15 * pow(x, 4) + 85 * pow(x, 3) - 225 * pow(x, 2) + 274 * x - 121;
}

int main() {
    for(double i=1.5000000; i<=2.4000000; i+=0.0000003) {
        if(fabs(f(i)) < eps) {
            printf("%.6lf", i);
            return 0;
        }
    }
}