#include <iostream>
#include "shape.h"
int main() {
    Rectangle recA(30, 40);
    std::cout << "Hello, Cmake" << std::endl;
    std::cout << "recA Size :" << recA.GetSize() << std::endl;
    return 0;
}
