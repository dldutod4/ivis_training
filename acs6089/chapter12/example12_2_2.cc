#include <iostream>

class A {
 public:
  A() { std::cout << "ctor\n"; }
  A(const A& a) { std::cout << "copy ctor\n"; }
  A(A&& a) { std::cout << "move ctor\n"; }
};

class B {
 public:
  //입력 받는 a는 좌측값이므로 이동 생성자를 사용할려면  
  //아래처럼 기본 생성자에서 다시 한번 move로 우측값으로 만들어줘야 이동생성자로 작동한다.
  B(A&& a) : a_(std::move(a)) {}

  A a_;
};

int main() {
  A a;
  std::cout << "create B-- \n";
  B b(std::move(a));
}