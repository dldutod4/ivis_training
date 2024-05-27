#include <iostream>

struct A {
    double d;
};

int main() {
    int a = 3;
    decltype(a) b = 2;  // int

    int& r_a = a;
    decltype(r_a) r_b = b;  // int&

    int&& x = 3;
    decltype(x) y = 2;  // int&&

    A* aa;
    decltype(aa->d) dd = 0.1;  // double
}