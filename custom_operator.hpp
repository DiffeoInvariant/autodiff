/**
 Based on code from
 https://github.com/klmr/named-operator
 */
#ifndef CUSTOM_OPERATOR_HPP
#define CUSTOM_OPERATOR_HPP

#include <utility>//std::declval
//binary operators
namespace base
{
    //holds an operator
    template <typename Op>
    struct operator_wrapper
    {
        Op oper;
    };
    
    //left and right-hand sides
    template <typename T, typename Op>
    struct operator_lhs
    {
        Op oper;
        T& value;
    };
    //less than operator takes in the lhs of the binary operator
    template <typename T, typename Op>
    operator_lhs<T, Op>
    operator <(T& lhs, operator_wrapper<Op> rhs){
        //initializer list for operator_lhs struct
        return {rhs.oper, lhs};
    }
    
    //same as above but for const T
    template <typename T, typename Op>
    operator_lhs<T const, Op>
    operator <(T const& lhs, operator_wrapper<Op> rhs){
        //initializer list for operator_lhs struct
        return {rhs.oper, lhs};
    }

    
    //greater than operator takes in rhs
    template <typename T1, typename T2, typename Op>
    auto operator >(operator_lhs<T1, Op> const& lhs, T2 const& rhs)
    -> decltype(lhs.oper(std::declval<T1>(), std::declval<T2>() ) ) {
        //modify and return reference to lhs
        return lhs.value = lhs.oper(lhs.value, rhs);
    }
    
    template <typename Op>
    constexpr operator_wrapper<Op>
    make_operator(Op oper) {
        //initializer list
        return {oper};
    }
    
    
}//end namespace base

#endif//CUSTOM_OPERATOR_HPP
