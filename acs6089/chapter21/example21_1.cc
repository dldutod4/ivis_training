#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

int main() {
    std::vector<std::unique_ptr<int>> v1;

    v1.push_back(std::make_unique<int>(1));
    v1.push_back(std::make_unique<int>(2));
    v1.push_back(std::make_unique<int>(3));

    // unique_ptr은 복사가 불가능하기에 다른 이동 반복자를 만들어 넣어 준다
    std::vector<std::unique_ptr<int>> v2(std::make_move_iterator(v1.begin()), std::make_move_iterator(v1.end()));

    for (auto& i : v2) {
        std::cout << *i << std::endl;
    }

    std::cout << v1.size() << std::endl;
    std::cout << v2.size() << std::endl;

    std::vector<std::string> v = {"hi", "hello", "abc"};
    for (const auto& s : v) {
        std::cout << s << std::endl;
    }
}