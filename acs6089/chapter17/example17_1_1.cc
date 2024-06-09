#include <iostream>

namespace detail {
template <class T>
char test(int T::*);
struct two {
    char c[2];
};
template <class T>
two test(...);
}  // namespace detail

template <class T>
struct is_class : std::integral_constant<bool, sizeof(detail::test<T>(0)) == 1 && !std::is_union<T>::value> {};

class something {};
struct example {};

int main() {
    std::cout << is_class<something>::value << std::endl;
    std::cout << is_class<example>::value << std::endl;  // is_class는 클래스와 공용체를 구별하는 기능이 없다
}