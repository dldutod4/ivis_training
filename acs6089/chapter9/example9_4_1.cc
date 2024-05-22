#include <iostream>

template <int N>
struct  INT
{
    static const int num = N;
};

template <typename a, typename b>
struct add
{
    typedef INT<a::num + b::num> result;
};

template <typename a, typename b>
struct divide
{
    typedef INT<a::num / b::num> result;
};

/*
template <>
struct divide<int a, int b> {
  const static int result = a + b;
};
*/

using one = INT<1>;
using two = INT<2>;
using three = INT<3>;

