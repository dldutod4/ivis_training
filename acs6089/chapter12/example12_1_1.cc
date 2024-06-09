#include <iostream>

class A {
  int data_;

 public:
  A(int data) : data_(data) { std::cout << "일반 생성자 호출!" << std::endl; }

  A(const A& a) : data_(a.data_) {
    std::cout << "복사 생성자 호출!" << std::endl;
  }
};

int main() {
  A a(1);  // 일반 생성자 호출
  A b(a);  // 복사 생성자 호출

  // 그렇다면 이것은?
  A c(A(2)); //일빈 생성자를 호출하고 복사 호출자를 호출할 것 같지만 실제로는 일반 호출자 한번한 호출된다
}