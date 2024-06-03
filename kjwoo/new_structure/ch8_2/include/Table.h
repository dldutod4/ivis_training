#ifndef TBL_H
#define TBL_H

#include <iostream>
#include <string>
#include "Cell.h"

using namespace std;

class Cell;
class Table
{
protected:
    // 행 및 열의 최대 크기
    int max_row_size, max_col_size;

    // 데이터를 보관하는 테이블
    // Cell* 을 보관하는 2차원 배열이라 생각하면 편하다
    Cell ***data_table;

public:
    Table(int max_row_size, int max_col_size) : max_row_size(max_row_size), max_col_size(max_col_size)
    {
        data_table = new Cell **[max_row_size];
        for (int i = 0; i < max_row_size; i++)
        {
            data_table[i] = new Cell *[max_col_size];
            for (int j = 0; j < max_col_size; j++)
            {
                data_table[i][j] = NULL;
            }
        }
    }

    ~Table();

    // 새로운 셀을 row 행 col 열에 등록한다.
    void reg_cell(Cell *c, int row, int col);

    // 해당 셀의 정수값을 반환한다.
    // s : 셀 이름 (Ex. A3, B6 과 같이)
    int to_numeric(const string &s);

    // 행 및 열 번호로 셀을 호출한다.
    int to_numeric(int row, int col);

    // 해당 셀의 문자열을 반환한다.
    string stringify(const string &s);
    string stringify(int row, int col);

    virtual string print_table() = 0;
};

class TxtTable : public Table
{
    string repeat_char(int n, char c);

    // 숫자로 된 열 번호를 A, B, .... Z, AA, AB, ...  이런 순으로 매겨준다.
    string col_num_to_str(int n);

public:
    TxtTable(int row, int col) : Table(row, col) {}

    // 텍스트로 표를 깨끗하게 출력해준다.
    string print_table();
};

class CsvTable : public Table
{
public:
    CsvTable(int max_row, int max_col) : Table(max_row, max_col) {
        
    }
    std::string print_table() override;
};
class HTMLTable : public Table
{
public:
    HTMLTable(int max_row, int max_col) : Table(max_row, max_col) {}
    std::string print_table() override;
};

#endif