#ifndef CELL_H
#define CELL_H
#include <string>
#include <ctime>
#include "Table.h"
#include "utils.h"

using namespace std;

class Table;
class Cell
{
protected:
    int x, y;
    Table *table;

public:
    virtual string stringify() = 0;
    virtual int to_numeric() = 0;

    Cell(int x, int y, Table *table);
};

class StringCell : public Cell
{
    string data;

public:
    string stringify();
    int to_numeric();

    StringCell(string data, int x, int y, Table *t);
};
class NumberCell : public Cell
{
    int data;

public:
    string stringify();
    int to_numeric();

    NumberCell(int data, int x, int y, Table *t);
};
class DateCell : public Cell
{
    time_t data;

public:
    string stringify();
    int to_numeric();

    DateCell(string s, int x, int y, Table *t);
};
class ExprCell : public Cell {
  string data;
  string* parsed_expr;

  Vector exp_vec;

  // 연산자 우선 순위를 반환합니다.
  int precedence(char c);

  // 수식을 분석합니다.
  void parse_expression();

 public:
  ExprCell(string data, int x, int y, Table* t);

  string stringify();
  int to_numeric();
};
#endif