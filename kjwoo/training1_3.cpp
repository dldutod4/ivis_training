/*
c언어의 아버지 bjarne stroustrup
1979년 c 에 클래스 도입
1982 c++
1998 첫 표준 c++98
2011 대격변 c++11 = modern c++

변수명 규칙 _ 기호 숫자 알파벳

변수, 포인터 등 차이없음
for문 차이없음, while 차이없음, if else 차이없음
switch break continue 도동일
 변수 선언 최상단에 없어도됨

cin이 변수를보고 포맷을 알아서 처리함


*/

#include <iostream>
int main(){
    // int i;
    // for (int i = 0; i < 10; i++)
    // {
    //     std::cout <<i << std::endl;
    // }
    // return 0;

    // ///////////////////////////////////
    // int i, sum =0;
    // for (int i = 1; i <= 10; i++)
    // {
    //     sum+=i;
    // }
    
    // std::cout <<"합은 :"<<sum <<std::endl;
    // return 0;
    //////////////////////////////////////
    int lucky_number = 3;
    std::cout << "내 비밀 수를 맞추어 보세요~" << std::endl;

    int user_input;  // 사용자 입력

    while (1) {
        std::cout << "입력 : ";
        std::cin >> user_input;
        if (lucky_number == user_input) {
        std::cout << "맞추셨습니다~~" << std::endl;
        break;
        } else {
        std::cout << "다시 생각해보세요~" << std::endl;
        }
    }
    return 0;
    
}