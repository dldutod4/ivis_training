#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <variant>

class A {
public:
    void a() { std::cout << "I am A" << std::endl; }
};

class B {
public:
    void b() { std::cout << "I am B" << std::endl; }
};

std::variant<A, B> GetDataFromDB(bool is_a) {
    if (is_a) {
        return A();
    }
    return B();
}

std::tuple<int, std::string, bool> GetStudent(int id) {
    if (id == 0) {
        return std::make_tuple(30, "철수", true);
    } else {
        return std::make_tuple(28, "영희", false);
    }
}

int main() {
    auto v = GetDataFromDB(true);

    std::cout << v.index() << std::endl;
    std::get<A>(v).a();  // 혹은 std::get<0>(v).a()

    std::tuple<int, double, std::string, unsigned int> tp;
    tp = std::make_tuple(1, 3.14, "hi", 255);

    std::cout << std::get<0>(tp) << ", " << std::get<1>(tp) << ", " << std::get<2>(tp) << ", " << std::get<3>(tp)
              << std::endl;

    auto student = GetStudent(1);

    auto [age, name, is_male] = student;

    std::cout << "이름 : " << name << std::endl;
    std::cout << "나이 : " << age << std::endl;
    std::cout << "남자 ? " << std::boolalpha << is_male << std::endl;
}