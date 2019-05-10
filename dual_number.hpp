#ifndef DUAL_NUMBER_HPP
#define DUAL_NUMBER_HPP
/**
 @author: Zane Jakobs
 @brief: dual numbers for automatic differentiation
 */
#include <ostream>

namespace dual
{
    //is_arithmetic<T>:: must be true
    template <typename T>
    class Dual
    {
    protected:
        //real part
        T x = 0.0;
        //non-real part
        T y = 0.0;
    public:
        //trivially constructible and descructible
        
        constexpr Dual(T x1, T y1) : x(x1), y(y1) {};
        
        
        constexpr auto real() const noexcept
        {
            return x;
        }
        
        constexpr auto dual() const noexcept
        {
            return y;
        }
        //returns 1 divided by *this
        constexpr Dual inv()
        {
            //check for divide-by-zero error
            if( x == 0 )
            {
                throw "Divide-by-zero error.";
            }
            auto xNew = 1/x;
            auto yNew = -1 * y/(x*x);
            return {xNew, yNew};
        }
        
        //overloaded addition
        constexpr Dual operator+(Dual rhs)
        {
            auto xNew = x + rhs.real();
            auto yNew = y + rhs.dual();
            //return with initializer list
            return {xNew, yNew};
        }
        //subtraction
        constexpr Dual operator-(Dual rhs)
        {
            auto xNew = x - rhs.real();
            auto yNew = y - rhs.dual();
            //return with initializer list
            return {xNew, yNew};
        }
        
        //multiplication
        constexpr Dual operator*(Dual rhs)
        {
            auto rr = rhs.real();
            auto xNew = x * rr;
            auto yNew = x * rhs.dual() + rr * y;
            
            return {xNew, yNew};
        }
        //division--not implemented very efficiently, calls Dual ctor twice
        constexpr Dual operator/(Dual rhs)
        {
            auto rInv = rhs.inv();
            return (*this) * rInv;
        }
        
        friend std::ostream& operator<<(std::ostream &os, Dual &num)
        {
            os << "(" << num.real() << "," << num.dual() << ")";
            return os;
        }
        
    };
}



#endif//DUAL_NUMBER_HPP
