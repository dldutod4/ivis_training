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
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <cctype>
class Table;
class Cell
{
protected:
    Table *table; // 어느 테이블에 속해있는지
    std::string data;
    int x, y; // 테이블 에서의 위치
public:
    friend Table;
    virtual double to_numeric() = 0;
    virtual std::string stringify() = 0;
    Cell(const std::string &data) : data(data){};
    Cell(const Cell &c)
    {
        table = c.table;
        data = c.data;
        x = c.x;
        y = c.y;
    };
};
class StringCell : public Cell
{
public:
    double to_numeric() override;
    std::string stringify() override;
};
double StringCell::to_numeric()
{
    return 0;
}
std::string StringCell::stringify()
{
    return data;
}

class NumberCell : public Cell
{
public:
    double to_numeric() override;
    std::string stringify() override;
};
double NumberCell::to_numeric()
{
    return std::stod(data);
}
std::string NumberCell::stringify()
{
    return data;
}

class DateCell : public Cell
{
    int year;
    int month;
    int date;

public:
    DateCell(std::string s) : Cell(s),
                              year(stoi(s.substr(0, 4))),
                              month(stoi(s.substr(4, 2))),
                              date(stoi(s.substr(6, 2))){};
    double to_numeric() override;
    std::string stringify() override;
};
double DateCell::to_numeric()
{
    return 0;
}
std::string DateCell::stringify()
{
    return data;
}

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

class ExprCell : public Cell
{

public:
    ExprCell(std::string s) : Cell(s) {}
    double to_numeric() override;
    std::string stringify() override;
};
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
class Table
{
    Cell ***data_base; // 왜 3중 포인터 인지 잘 생각해보세요!
    // cell*를 보관하는 이차원배열
protected:
    int max_row;
    int max_col;

public:
    friend ExprCell; // 연산을위해 다른 셀에 접근할 필요가 있음.
    Table(int max_row, int max_col);
    virtual std::string print_table() = 0;      // 가상함수
    void reg_cell(Cell *c, int row, int col);   // Cell 을 등록한다
    std::string get_cell_std(int row, int col); // 해당 위치의 Cell 데이터를 얻는다.
    ~Table();
};

std::ostream &operator<<(std::ostream &o, Table &t)
{
    o << t.print_table();
    return o;
}
Table::Table(int max_row, int max_col) : max_row(max_row), max_col(max_col)
{
    data_base = new Cell **[max_row];
    for (int i = 0; i < max_row; i++)
    {
        data_base[i] = new Cell *[max_col];
    }
    for (int i = 0; i < max_row; i++)
    {
        for (int j = 0; j < max_col; j++)
        {
            data_base[i][j] = nullptr;
        }
    }
}
Table::~Table()
{
    for (int i = 0; i < max_row; i++)
    {
        for (int j = 0; j < max_col; j++)
        {
            if (data_base[i][j])
                delete data_base[i][j];
        }
    }
    for (int i = 0; i < max_row; i++)
    {
        delete[] data_base[i];
    }
    delete[] data_base;
}
void Table::reg_cell(Cell *c, int row, int col)
{
    // 셀 정보 주입
    c->table = this;
    c->x = col;
    c->y = row;
    // db에 등록
    data_base[row][col] = c;
    return;
}
std::string Table::get_cell_std(int row, int col)
{
    if (data_base[row][col] != nullptr)
    {
        return data_base[row][col]->data;
    }
    else
    {
        return "empty";
    }
}
class TextTable : public Table
{
public:
    TextTable(int max_row, int max_col) : Table(max_row, max_col) {}
    std::string print_table() override;
};
std::string TextTable::print_table()
{
    std::string s;

    for (int i = 0; i < max_row; i++)
    {
        for (int j = 0; j < max_col; j++)
        {
            s = s + get_cell_std(i, j);
            s += ' ';
        }
        s += '\n';
    }
    return s;
}
class CsvTable : public Table
{
public:
    CsvTable(int max_row, int max_col) : Table(max_row, max_col) {}
    std::string print_table() override;
};
std::string CsvTable::print_table()
{
    std::string s;

    for (int i = 0; i < max_row; i++)
    {
        for (int j = 0; j < max_col; j++)
        {
            s = s + get_cell_std(i, j);
            if (j != max_col - 1)
                s += ',';
        }
        s += '\n';
    }
    return s;
}
class HTMLTable : public Table
{
public:
    HTMLTable(int max_row, int max_col) : Table(max_row, max_col) {}
    std::string print_table() override;
};
std::string HTMLTable::print_table()
{
    std::string s;
    s += "<table>\n";
    for (int i = 0; i < max_row; i++)
    {
        s += "    <tr>\n";
        for (int j = 0; j < max_col; j++)
        {
            s += "        <th>";
            s += get_cell_std(i, j);
            s += "</th>\n";
        }
        s += "    </tr>\n";
    }
    s += "</table>";
    return s;
}

int main()
{
    TextTable tbl(10,10);
    
    ExprCell exp("9*9-8*8-7*7");
    ExprCell exp2("7*7");
    DateCell date("20240505");
    tbl.reg_cell(&exp,0,0);
    tbl.reg_cell(&exp2,0,2);
    tbl.reg_cell(&date,0,1);


    std:: cout << "결과:"<< exp.to_numeric()<<std::endl;
    std::cout <<tbl;
}