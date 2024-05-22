#include <iostream>

int fibo(int n)
{
    if(n==1 || n==2)return 1;
    return fibo(n-1) + fibo(n-2);
}

template <int N>
struct fib
{
    static const int result = fib<N-1>::result + fib<N-2>::result;
};

template <>
struct fib<1>
{
    static const int result = 1;
};

template <>
struct fib<2>
{
    static const int result = 1;
};

int main()
{
    std::cout << fibo(6) << std::endl;
    std::cout << fib<6>::result << std::endl;
}