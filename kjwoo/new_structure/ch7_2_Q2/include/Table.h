#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <string>

#include "Cell.h"

//class Cell;
class Table {
private:
protected:
    int max_row;
    int max_col;
public:
    Cell*** data_base;
    Table(int max_row, int max_col);
    virtual std::string print_table()= 0;
    void reg_cell(Cell* c, int row, int col);
    std::string get_cell_std(int row, int col);
    ~Table();
};


class TextTable : public Table
{
public:
    TextTable(int max_row, int max_col) : Table(max_row, max_col) {}
    std::string print_table() override;
};
class CsvTable : public Table
{
public:
    CsvTable(int max_row, int max_col) : Table(max_row, max_col) {}
    std::string print_table() override;
};
class HTMLTable : public Table
{
public:
    HTMLTable(int max_row, int max_col) : Table(max_row, max_col) {}
    std::string print_table() override;
};

#endif // TABLE_H
