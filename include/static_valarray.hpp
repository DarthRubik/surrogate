#ifndef STATIC_VALARRAY_HPP
#define STATIC_VALARRAY_HPP
#include <cstdint>
#include <utility>

namespace surrogate{


template<typename value_t, std::size_t size>
struct static_valarray
{
    // Purposefully an aggregate for aggregate initialization
    value_t data[size];
#define UNARY_OPERATOR(op, constness)\
    constexpr auto operator op() constness\
    {\
        using new_type = decltype(op std::declval<value_t constness>());\
        static_valarray<new_type,size> ret;\
        for (std::size_t x = 0; x < size; x++)\
            ret.data[x] = op this->data[x];\
        return ret;\
    }

    UNARY_OPERATOR(+,)
    UNARY_OPERATOR(+,const)

    UNARY_OPERATOR(-,)
    UNARY_OPERATOR(-,const)

    UNARY_OPERATOR(~,)
    UNARY_OPERATOR(~,const)

    UNARY_OPERATOR(!,)
    UNARY_OPERATOR(!,const)

#define COMPOUND_ASSIGN_ARR(op)\
    constexpr static_valarray& operator op(static_valarray const& other)\
    {\
        for (std::size_t x = 0; x < size; x++)\
            this->data[x] op other.data[x];\
        return *this;\
    }

    COMPOUND_ASSIGN_ARR(+=)
    COMPOUND_ASSIGN_ARR(-=)
    COMPOUND_ASSIGN_ARR(*=)
    COMPOUND_ASSIGN_ARR(/=)
    COMPOUND_ASSIGN_ARR(%=)
    COMPOUND_ASSIGN_ARR(&=)
    COMPOUND_ASSIGN_ARR(|=)
    COMPOUND_ASSIGN_ARR(^=)
    COMPOUND_ASSIGN_ARR(<<=)
    COMPOUND_ASSIGN_ARR(>>=)


#define BINARY_OPERATOR(op)\
    constexpr friend auto operator op\
        (static_valarray const& a, static_valarray const& b)\
    {\
        using new_type = decltype(a.data[0] op b.data[0]);\
        static_valarray<new_type,size> ret;\
        for (std::size_t x = 0; x < size; x++)\
            ret.data[x] = a.data[x] op b.data[x];\
        return ret;\
    }

    BINARY_OPERATOR(+)
    BINARY_OPERATOR(-)
    BINARY_OPERATOR(*)
    BINARY_OPERATOR(/)
    BINARY_OPERATOR(%)
    BINARY_OPERATOR(&)
    BINARY_OPERATOR(|)
    BINARY_OPERATOR(^)
    BINARY_OPERATOR(<<)
    BINARY_OPERATOR(>>)
    BINARY_OPERATOR(&&)
    BINARY_OPERATOR(||)

    BINARY_OPERATOR(==)
    BINARY_OPERATOR(!=)
    BINARY_OPERATOR(>=)
    BINARY_OPERATOR(<=)
    BINARY_OPERATOR(>)
    BINARY_OPERATOR(<)
};


}
#endif
