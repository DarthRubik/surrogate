#include <cassert>
#include <static_valarray.hpp>
#include <type_traits>


int main()
{
    {
        // Test unary plus
        int array[3] = { 1, 2, 3};
        using array_t = decltype(array);
        using test_t = static_valarray<array_t,2>;
        test_t x = {
            {
                {1,2,3},
                {4,5,6}
            }
        };

        //Unary plus operator on arrays decays into a pointer
        auto thing = +x;
        // Since this is a pointer the original will change
        thing.inner[0][0] = 12;
        assert(x.inner[0][0] == 12);
        static_assert(
            std::is_same<
                static_valarray<int*,2>,
                decltype(thing)
            >::value, "");

        auto other_thing = +const_cast<test_t const&>(x);
        assert(other_thing.inner[0][0] == 12);
        static_assert(
            std::is_same<
                static_valarray<int const*,2>,
                decltype(other_thing)
            >::value, "");
    }

    {
        using test_t = static_valarray<int, 3>;

        test_t x = { 1, 2, 3 };

        x += x;
        assert(x.inner[0] == 2);
        assert(x.inner[1] == 4);
        assert(x.inner[2] == 6);
    }
}
