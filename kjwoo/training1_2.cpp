#include <iostream>
/*
    namespace - 정의된 객체에 대해 어디 소속인지 지정해주는 것

    namespace header1{
        int foo();
    }

    namespace header2{
        int foo();
    }

    자신이 포함된 namespace내에서는 namespace를 명시하지않아도 된다.
    다른 namespace의 것을 부를때는 header1::foo(); 처럼 사용
    어떤 namespace에도 소속되지않으면 명시적으로 정해야함

    특정 namespace에 정의된 것들을 명시없이 사용하고싶으면
    using namespace header1; 으로 사용가능 그러나 권장하진않는다
    이름이 겹치는 함수가 있을 수 있기 때문.
    
    namespace에 이름을 설정하지 않을 수도 있다 - 해당 파일안에서만 접근할 수 있게된다.(static과 유사한 효과)

*/
namespace {
    int OnlyInThisFile(){
    };
    int onlyInThisFile = 0;
}
int main(){
    std::cout <<"Hello, World!!" << std::endl; 
    //cout은 ostream 클래스의 객체로 표준출력을 담당 (c언어의 stdout)
    //endl은 함수로 화면에 엔터를 출력함
    OnlyInThisFile();
    return 0;
}