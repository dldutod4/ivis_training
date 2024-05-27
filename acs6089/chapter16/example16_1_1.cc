#include <initializer_list>
#include <iostream>

class A {
public:
    A(int x, double y) { std::cout << "일반 생성자! " << std::endl; }

    A(std::initializer_list<int> lst) { std::cout << "초기화자 사용 생성자! " << std::endl; }
};

int main() {
    auto a = {1};     // 첫 번째 형태이므로 std::initializer_list<int>
    auto b{1};        // 두 번째 형태 이므로 그냥 int
    auto c = {1, 2};  // 첫 번째 형태이므로 std::initializer_list<int>
    // auto d{1, 2};     // 두 번째 형태 인데 인자가 2 개 이상이므로 컴파일 오류
}