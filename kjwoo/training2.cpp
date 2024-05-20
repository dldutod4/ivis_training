/*
cpp 신개념 참조자(레퍼런스)

int&, double&, int*& ...
int& another_a = a;
a 변수의 또다른 이름 another_a를 선언

레퍼런스 정의시에는 반드시 누구의 별명인지 명시해야함
포인터와 달리 int& another_a; 가 불가

+ 레퍼런스가 한번 별명이 되면 절대 다른 이의 별명으로 변경할 수 없음

레퍼런스에 항상 메모리가 할당되진 않는다
불필요한 &와 *를 안써도된다.

상수에대한 참조자
int &ref =4;
ref=5;
같은 것은 불가능

const int &ref =4; 상수로 지정하면 가능
로하면 리터럴 참조 가능
a=ref; == a=4;

? 리터럴
소스코드 상에서 고정된 값을 가지는 것
큰 따옴표로 묶인 경우 문자열 리터럴이라 부름 ex "good"
프로그램 실행시 리터럴들이 보관된 공간이 생성됨
리터럴은 변경될 수 없음

레퍼런스의 배열은 불가능
int& arr[2] = {a,b} -> x
특별한 경우 외에는 레퍼런스는 메모리상에 존재하지않아 주소값으로 변환이 안됨
arr+2같은 연산이 안되기때문

배열의 레퍼런스는 가능
int (&ref)[3][2] -- [3][2] 의 2차원 int배열의 레퍼런스

레퍼런스를 리턴할 경우
int& func(){
    int a =2;
    return a;
}
를 할 경우
int& ref = a;
와 같은데 지역변수 a는 func 종료와 함께 소멸하므로 ref는 참조할 변수가 사라진다.
이 경우를 dangling 레퍼런스라고 부른다.
지역 변수의 레퍼런스를 리턴하지 않도록 조심

int& function(int& a) {
  a = 5;
  return a;
}
외부 참조자를 리턴하는경우
레퍼런스의 타입과 크기에 상관없이 주소값복사 한번으로 전달이 끝나게된다.

참조자가아닌 값을 리턴하는 함수를 참조자로 받기
리턴하는 참조자가 아닌값은 문장종료후 소멸하기때문에 댕글링 레퍼런스가 되어 오류가 발생한다.

그러나 예외적으로 const 레퍼런스로 받으면 사용이 가능하다.



*/

// #include <iostream>

// int change_val(int *p) { // 2 포인터 변수 p로 받아
//   *p = 3; // 3 값 변경

//   return 0;
// }
// int main() {
//   int number = 5;

//   std::cout << number << std::endl;
//   change_val(&number); //1 number의 주소를 넘겨서
//   std::cout << number << std::endl;
// }
///////////////////////////////////////
// #include <iostream>

// int main() {
//   int a = 3;
//   int& another_a = a;

//   another_a = 5;
//   std::cout << "a : " << a << std::endl;
//   std::cout << "another_a : " << another_a << std::endl;

//   return 0;
// }

#include <iostream>

int main() {
  int x;
  int& y = x;
  int& z = y; // z또한 x의 참조자가 된다 
  //참조자의 참조자를 만드는 것은 금지돼있다.

  x = 1;
  std::cout << "x : " << x << " y : " << y << " z : " << z << std::endl;

  y = 2;
  std::cout << "x : " << x << " y : " << y << " z : " << z << std::endl;

  z = 3;
  std::cout << "x : " << x << " y : " << y << " z : " << z << std::endl;
}
