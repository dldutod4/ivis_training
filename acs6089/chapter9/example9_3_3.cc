#include <iostream>

int gcd(int a, int b)
{
    if(b==0)return a;
    return gcd(b, a%b);
}

template <int X, int Y>
struct GCD
{
    static const int value = GCD<Y, X%Y>::value;
};

template <int X>
struct  GCD<X,0>
{
    static const int value = X;
};

int main()
{
    std::cout << GCD<36, 24>::value << std::endl;
    std::cout << gcd(36, 24) << std::endl;
    return 0;
}