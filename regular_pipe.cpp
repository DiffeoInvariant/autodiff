
#include "custom_operator.hpp"
#include "dual_number.hpp"
#include <iostream>

namespace op
{
    //evaluate functions f: T -> T
    template<class T, class Func>
    T ueval(T arg, Func&& f){
        return f(arg);
    }
}

auto ueval = base::make_operator(op::ueval<double, double(&&)(double)>);

auto deval = base::make_operator(op::ueval<dual::Dual<double>, dual::Dual<double>(&&)(dual::Dual<double>)>);

template <typename T>
T test_poly(T x){
    /**
     returns 1 + 7.5*x + x^2 + 3.2 * x^3
     */
    auto x2 = x*x;
    return 1.0 + 7.5*x + x2 + 3.2*x*x2;
}

template <typename T>
T dual_poly(T x)
{
    return x + x*x + x*x*x;
}
//divides by test result of above
double divide_by_6199(double in)
{
    return in / 6199.3144;
}

int main()
{
    double x0 = 12.3;
    
    std::cout << "Testing test_poly<double>(12.3). Expected 6199.3144. \n";
    auto x1 = x0 <ueval> test_poly<double>;
    std::cout << x1 << '\n';
    
    std::cout << "Testing divide_by_6199(x1). Expected 1.\n";
    auto x1Inv = x1 <ueval> divide_by_6199;
    std::cout << x1Inv << '\n';
    
    std::cout << "Testing dual number ctor. Expected (3.2,1.0).\n";
    
    dual::Dual dnum(3.2,1.0);
    std::cout << dnum << '\n';
    
    std::cout << "Testing test_poly<dual::Dual<double>>. Expected (46.208, 38.12), which\n";
    std::cout << "is (f(3.2), f'(3.2)), where f(x) = x + x^2 + x^3.\n";
    auto d2 = dnum <deval> dual_poly<dual::Dual<double>>;
    std::cout << d2 << '\n';
    
    return 0;
}
