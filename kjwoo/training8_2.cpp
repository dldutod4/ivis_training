#include<ctime>
#include<string>
#include <cctype>
#include"utils.h"
using namespace std;

class StringCell : public Cell {
  string data;

 public:
  string stringify();
  int to_numeric();

  StringCell(string data, int x, int y, Table* t);
};
class NumberCell : public Cell {
  int data;

 public:
  string stringify();
  int to_numeric();

  NumberCell(int data, int x, int y, Table* t);
};
class DateCell : public Cell {
  time_t data;

 public:
  string stringify();
  int to_numeric();

  DateCell(string s, int x, int y, Table* t);
};
Cell::Cell(int x, int y, Table* table) : x(x), y(y), table(table) {}

StringCell::StringCell(string data, int x, int y, Table* t)
    : data(data), Cell(x, y, t) {}
string StringCell::stringify() { return data; }
int StringCell::to_numeric() { return 0; }

/*


NumberCell


*/
NumberCell::NumberCell(int data, int x, int y, Table* t)
    : data(data), Cell(x, y, t) {}

string NumberCell::stringify() { return to_string(data); }
int NumberCell::to_numeric() { return data; }

/*


DateCell


*/
string DateCell::stringify() {
  char buf[50];
  tm temp;
  localtime_s(&temp, &data);

  strftime(buf, 50, "%F", &temp);

  return string(buf);
}
int DateCell::to_numeric() { return static_cast<int>(data); }

DateCell::DateCell(string s, int x, int y, Table* t) : Cell(x, y, t) {
  // 입력받는 Date 형식은 항상 yyyy-mm-dd 꼴이라 가정한다.
  int year = atoi(s.c_str());
  int month = atoi(s.c_str() + 5);
  int day = atoi(s.c_str() + 8);

  tm timeinfo;

  timeinfo.tm_year = year - 1900;
  timeinfo.tm_mon = month - 1;
  timeinfo.tm_mday = day;
  timeinfo.tm_hour = 0;
  timeinfo.tm_min = 0;
  timeinfo.tm_sec = 0;

  data = mktime(&timeinfo);
}

int ExprCell::to_numeric() {
  double result = 0;
  NumStack stack;

  for (int i = 0; i < exp_vec.size(); i++) {
    string s = exp_vec[i];

    // 셀 일 경우
    if (isalpha(s[0])) {
      stack.push(table->to_numeric(s));
    }
    // 숫자 일 경우 (한 자리라 가정)
    else if (isdigit(s[0])) {
      stack.push(atoi(s.c_str()));
    } else {
      double y = stack.pop();
      double x = stack.pop();
      switch (s[0]) {
        case '+':
          stack.push(x + y);
          break;
        case '-':
          stack.push(x - y);
          break;
        case '*':
          stack.push(x * y);
          break;
        case '/':
          stack.push(x / y);
          break;
      }
    }
  }
  return stack.pop();
}