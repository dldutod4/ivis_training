#ifndef CELL_H
#define CELL_H
#include<iostream>
#include <vector>
#include <stack>
#include <string>
#include"Table.h"
//class Table;
class Cell {
private:
    
    
    int x;
    int y;

protected:
    std::string data;

public:
    friend Table;
    Table* table;
    Cell();
    Cell(const std::string& data);
    virtual int to_numeric() = 0;
    virtual std::string stringify() = 0;
    
};

class StringCell : public Cell {
public:
    StringCell(std::string s):Cell(s){};
    int to_numeric() override;
    std::string stringify() override;
};

class NumberCell : public Cell {
    double num;
public:
    NumberCell(std::string s):Cell(s),num(std::stod(s)){};
    int to_numeric() override;
    std::string stringify() override;
};

class DateCell : public Cell {
public:
    DateCell(std::string s):Cell(s){};
    int to_numeric() override;
    std::string stringify() override;
};

class ExprCell : public Cell {
public:
    ExprCell(std::string s):Cell(s){};    
    int to_numeric() override;
    std::string stringify() override;
};

#endif // CELL_H