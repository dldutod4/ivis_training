/* 컴파일 타임 팩토리얼 계산 */
#include <iostream>


template <int N>

//팩토리얼 연산은 자신에서 계속 1을 빼가며 연산하기 때문에 재귀 형태가 필요하다
struct Factorial {
  static const int result = N * Factorial<N - 1>::result;
};

template <>

//숫자를 계속 빼다 빼고난 숫자가 1이되면 재귀를 멈춘다
struct Factorial<1> {
  static const int result = 1;
};

int main() {
  std::cout << "6! = 1*2*3*4*5*6 = " << Factorial<6>::result << std::endl;
}