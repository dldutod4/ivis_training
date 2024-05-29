#include <iostream>
#include <optional>
#include <utility>

class A {
public:
    A() { std::cout << "디폴트 생성" << std::endl; }

    A(const A& a) { std::cout << "복사 생성" << std::endl; }
};

int main() {
    A a;

    std::cout << "Optional 객체 만듦 ---- " << std::endl;
    std::optional<A> maybe_a;

    std::cout << "maybe_a 는 A 객체를 포함하고 있지 않기 때문에 디폴트 생성할 "
                 "필요가 없다."
              << std::endl;
    maybe_a = a;
}