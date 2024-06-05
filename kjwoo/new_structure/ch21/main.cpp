#include <iostream>
#include <memory>
#include <vector>

int main() {
    std::vector<std::unique_ptr<int>> v1;

    v1.push_back(std::make_unique<int>(1));
    v1.push_back(std::make_unique<int>(2));
    v1.push_back(std::make_unique<int>(3));

    std::vector<std::unique_ptr<int>> v2(std::make_move_iterator(v1.begin()), std::make_move_iterator(v1.end()));

    std::cout << v1.size() << std::endl;
    std::cout << v2.size() << std::endl;
    // std::cout << *v1[0] << std::endl;
    std::cout << *v1[2] << std::endl;
    return 0;
}
