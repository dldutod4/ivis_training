//  문제 2 (난이도 :最上 - 위의 문제와 이어집니다)

// 하지만 실제 엑셀의 경우 셀이 문자열 데이터만 들어가는 것이 아니라,
// 숫자나 날짜 심지어 수식 까지도 들어갈 수 있습니다.
// 따라서 우리는 Cell 을 상속 받는 4 개의 StringCell. NumberCell, DateCell, ExprCell 클래스들을
// 만들어야 합니다.

// 또한 Cell 클래스에 to_numeric (데이터를 숫자로 바꾼다)과
// std::stringify (데이터를 문자열로 바꾼다) 함수들을 가상으로 정의하고,
// 4개의 클래스들이 이를 상속 받아서 구현할 수 있게 해야 합니다.
// (참고로 문자열을 숫자로 변환하면 그냥 0 이 되게 하면 됩니다)

// 또한 ExprCell 의 경우 간단한 수식에 대한 정보를 가지는 객체로,
// Cell 들 간의 연산을 사용할 수 있습니다.
// 에를 들어서 A1+B2+C6-6 와 같은 데이터가 들어 있는 ExprCell 에 to_numeric 함수를 호출하면
// A1, B2, C6 의 값을 더하고 (각 셀에 to_numeric 을 해서), 6 을 빼준 결과값이 와야 합니다.나

// 참고로 프로그래밍의 편의를 위해서 ExprCell 의 경우,
// 셀을 지칭하는 것은 딱 두 글자 (A1, Z9 처럼) 로 하고, 숫자는 오직 한 자리 수 정수,
// 그리고 가능한 연산자는 +, -, *, / 로 하겠습니다.

/*
 */

#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <cctype>
#include"cell.h"
#include"table.h"


// 계산 전략
/*

곱셈 나눗셈은 쌓아서 처리해야함
덧셈과 뺄셈은 즉각처리
덧셈과 뺄셈을 이후에 처리
피연산자가 나오면 일단 스택에 넣는다

연산자
+ or -
연산자 스택에 *이나 /가 있으면
피연산자 스택에서 빼서 연산자스택에서 *나 /가 안나올때 까지 계산한다.
다 계산하면 계산결과를 피연산자스택에 넣고 연산자 스택에 + or -를 넣는다.

* or /
연산자 스택에 추가한다



1:

*/



std::ostream &operator<<(std::ostream &o, Table &t)
{
    o << t.print_table();
    return o;
}


int main()
{
    TextTable tbl(10,10);
    
    ExprCell exp("9*9-8*8-7*7");
    DateCell date("20240505");
    //tbl.reg_cell(&exp,0,0);
    //tbl.reg_cell(&date,0,1);

    std:: cout << "결과:"<< exp.to_numeric()<<std::endl;
    std::cout <<tbl;
}