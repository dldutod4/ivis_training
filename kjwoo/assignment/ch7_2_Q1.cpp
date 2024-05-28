//  문제 1 (난이도 :中)

// 일단 엑셀의 셀들의 정보 (일단 단순한 std::string 이라고 생각합시다) 에 대한
//  Cell 클래스가 있고 이 Cell 객체들을 모아두는 Table 클래스가 있습니다.
//  Table 클래스에는 2차원 배열로 Cell 객체들에 대한 정보
//  (참고로 Cell 객체가 생성 될 때 마다 동적으로 Cell 객체를 생성합니다.) 가 보관되어 있습니다.
//  또한 Table 클래스에 전체 데이터를 출력하는 print_table 함수가 가상으로 정의되어 있습니다.

// 여러분은 Table 클래스를 상속 받는 TextTable,
// CSVTable, HTMLTable 클래스를 만들어서 print_table 함수를 오버라이드 할 함수들을 제작할 것
// 입니다. 예를 들어 TextTable 클래스의 print_table 함수는 텍스트 형식으로,
// CSVTable 은 CSV 파일 형식으로 등등 만들어야 겠지요?
// 제가 아래 대충 프로그램의 골격을 잡아 놓았으니 여러분들은 이를 채우기만 하면 됩니다.

/*
 */
#include <iostream>
#include <string>
#include<fstream>
class Table;
class Cell
{
    Table *table; // 어느 테이블에 속해있는지
    std::string data;
    int x, y; // 테이블 에서의 위치
public:
    friend Table;
    Cell(const std::string &data) : data(data){};
    Cell(const Cell& c){
        table = c.table;
        data = c.data;
        x=c.x;
        y=c.y;
    };
};

class Table
{
    Cell ***data_base; // 왜 3중 포인터 인지 잘 생각해보세요!
    // cell*를 보관하는 이차원배열
protected:
    int max_row;
    int max_col;

public:
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
    data_base[row][col] = new Cell(*c);
    return;
}
std::string Table::get_cell_std(int row, int col){
    if (data_base[row][col] != nullptr){
        return data_base[row][col]->data;
    }else{
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
            s =s + get_cell_std(i, j);
            s += ' ';
        }
        s += '\n';
    }
    return s;
}class CsvTable : public Table
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
            s =s + get_cell_std(i, j);
            if(j!=max_col-1) s += ',';
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
    s+="<table>\n";
    for (int i = 0; i < max_row; i++)
    {
        s+="    <tr>\n";
        for (int j = 0; j < max_col; j++)
        {
            s +="        <th>";
            s += get_cell_std(i, j);
            s +="</th>\n";

        }
        s += "    </tr>\n";
    }
    s += "</table>";
    return s;
}


int main()
{
    HTMLTable tb(5, 4);
    Cell a("hihi");
    tb.reg_cell(&a,1,1);
    std::cout << tb;
    std::ofstream out("table1.txt");
    if(out.is_open()){
        out << tb;
    }
    
}