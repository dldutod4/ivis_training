#ifndef TBL_H
#define TBL_H
//#include "cell.h"
#include<string>
class Cell;
class Table
{
    
    // cell*를 보관하는 이차원배열
protected:
    
    int max_row;
    int max_col;

public:
    Cell ***data_base; // 왜 3중 포인터 인지 잘 생각해보세요!
    //friend ExprCell; // 연산을위해 다른 셀에 접근할 필요가 있음.
    Table(int max_row, int max_col);
    virtual std::string print_table() = 0;      // 가상함수
    void reg_cell(Cell *c, int row, int col);   // Cell 을 등록한다
    std::string get_cell_std(int row, int col); // 해당 위치의 Cell 데이터를 얻는다.
    ~Table();
};
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

#endif