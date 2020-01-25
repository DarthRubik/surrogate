#ifndef STATIC_VALARRAY_HPP
#define STATIC_VALARRAY_HPP
#include <cstdint>
#include <utility>


template<typename value_t, std::size_t size>
struct static_valarray
{
    // Purposefully an aggregate for aggregate initialization
    value_t inner[size];
#define UNARY_OPERATOR(op, constness)\
    constexpr auto operator op() constness\
    {\
        using new_type = decltype(op std::declval<value_t constness>());\
        static_valarray<new_type,size> ret;\
        for (std::size_t x = 0; x < size; x++)\
            ret.inner[x] = op this->inner[x];\
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
};

#endif
