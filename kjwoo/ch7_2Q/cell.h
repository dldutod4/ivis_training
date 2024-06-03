#ifndef CLL_H
#define CLL_H
#include"table.h"
#include <stack>
#include<string>
#include <vector>
#include <iostream>
using namespace std;
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

class NumberCell : public Cell
{
public:
    double to_numeric() override;
    std::string stringify() override;
};

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
class ExprCell : public Cell
{

public:
    ExprCell(std::string s) : Cell(s) {}
    double to_numeric() override;
    std::string stringify() override;
};
#endif