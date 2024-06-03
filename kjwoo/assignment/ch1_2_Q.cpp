// 문제 1

//     화면에 출력되는 것들을 바꾸어보자.
#include <iostream>
    namespace
{
    int OnlyInThisFile() {
    };
    int onlyInThisFile = 0;
}
int main()
{
    std::cout << "Hello, World!!" << std::endl;
    // cout은 ostream 클래스의 객체로 표준출력을 담당 (c언어의 stdout)
    // endl은 함수로 화면에 엔터를 출력함
    OnlyInThisFile();
    return 0;
}

//  문제 2

// 아래 문장은 화면에 어떻게 출력될까요?

// std::cout << "hi" << std::endl
//           << "my name is "
//           << "Psi" << std::endl;

//hi
//my name is Psi
