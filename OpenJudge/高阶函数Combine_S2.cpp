#include <functional>
template<typename T1, typename T2, typename T3>
auto combine(T1 f1, T2 f2) -> function<double(double)> {
    return [&](T3 x){return f1(f1(x) + f2(x));};
}