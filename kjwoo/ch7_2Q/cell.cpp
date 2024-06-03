#include"cell.h"


double StringCell::to_numeric()
{
    return 0;
}
std::string StringCell::stringify()
{
    return data;
}

double NumberCell::to_numeric()
{
    return std::stod(data);
}
std::string NumberCell::stringify()
{
    return data;
}

double DateCell::to_numeric()
{
    return 0;
}
std::string DateCell::stringify()
{
    return data;
}


double ExprCell::to_numeric()
{
    std::stack<double> ops; // 피연산자스택 *,/용
    std::stack<char> opers; // 연산자스택 *,/용
    std::vector<double>ops2; // 피연산자스택 +,-용
    std::vector<char>opers2; // 연산자스택 +,-용
    std::cout<<"연산시작"<<std::endl;
    for (int i = 0; i < data.length(); i++)
    {
        if (isdigit(data[i])) // 숫자일때 ops에 추가
        {
            std::cout<<"숫자추가:"<<atoi(&data[i])<<std::endl;
            ops.push(atoi(&data[i])); 
        }
        else if (data[i] >= 'A' && data[i] <= 'Z') // 문자일때
        { 
            int row = data[i] - 'A';
            int col = atoi(&data[++i]);     
            table->data_base[row][col]->to_numeric();                           // 두글자 확인.
            ops.push(table->data_base[row][col]->to_numeric()); // 해당 셀 값을 받아와 ops스택에 저장.
            ops.push(10); //임시
            
        }
        else if (data[i] == '*' || data[i] == '/') //곱 나눗셈일때
        {
            opers.push(data[i]); //연산자 opers에 저장.
        }
        else if (data[i] == '+' || data[i] == '-')
        {
            while (!opers.empty() && (opers.top() == '*' || opers.top() == '/'))
            {
                if (opers.top() == '*')
                { // operand 2개를 빼서 곱한후 다시 push
                    std::cout<<"곱연산"<<std::endl;
                    double op1 = ops.top();
                    ops.pop();
                    double op2 = ops.top();
                    ops.pop();
                    ops.push(op2 * op1);
                    std::cout<<"곱연산끝"<<std::endl;
                }
                else
                {
                    double op1 = ops.top();
                    ops.pop();
                    double op2 = ops.top();
                    ops.pop();
                    ops.push(op2 / op1); // 역순으로 빠지므로 역순으로 연산한다.
                }
                opers.pop();
            }
             opers.push(data[i]);//+ or - push
        }
    }
    while (!opers.empty() && (opers.top() == '*' || opers.top() == '/')) //끝났을때 opers스택을 마저 비운다.
        {
            if (opers.top() == '*')
            { // operand 2개를 빼서 곱한후 다시 push
                std::cout<<"곱연산"<<std::endl;
                double op1 = ops.top();
                ops.pop();
                double op2 = ops.top();
                ops.pop();
                ops.push(op2 * op1);
                std::cout<<"곱연산끝"<<std::endl;
            }
            else
            {
                double op1 = ops.top();
                ops.pop();
                double op2 = ops.top();
                ops.pop();
                ops.push(op2 / op1); // 역순으로 빠지므로 역순으로 연산한다.
            }
            opers.pop();
        }
    std::cout<<"스택처리 완료"<<std::endl;
    //남은 + - 연산
    //벡터에 다시 넣는다.
    while(!ops.empty()){
        std::cout<<ops.top()<<std::endl;
        ops2.push_back(ops.top());
        ops.pop();
    }
    while(!opers.empty()){
        opers2.push_back(opers.top());
        opers.pop();
    }
    while(!opers2.empty()){ //뒤부터 빼면서 덧셈 뺄셈 연산.
        char oper = opers2.back();
        opers2.pop_back();
        double op1 = ops2.back();
        ops2.pop_back();
        double op2 = ops2.back();
        ops2.pop_back();
        if(oper == '+'){          
            ops2.push_back(op1+op2);
        }else{
            ops2.push_back(op1-op2);
        }
    }
    std::cout<<"연산종료"<<std::endl;
    return ops2.back();
}
std::string ExprCell::stringify()
{
    return data;
}

