#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using std::vector;

class A {
    int id;

public:
    A(int x) : id(x) {}
    int mem1(int x, int y) {
        std::cout << "id:" << id + x + y << std::endl;
        return id;
    }
};
int main() {
    std::vector<int> vec(10);
    std::function<int(A&, int, int)> f5 = &A::mem1;
    std::function<int(const vector<int>&)> f6 = &vector<int>::size;
    std::cout << f6(vec) << std::endl;

    A a(11);
    std::cout << f5(a, 2, 3);
}
