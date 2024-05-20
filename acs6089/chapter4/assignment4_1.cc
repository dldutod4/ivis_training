#include <iostream>

class Date {
  int year_;
  int month_;  // 1 부터 12 까지.
  int day_;    // 1 부터 31 까지.
  int everymonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

 public:
  void SetDate(int year, int month, int date)
  {
    year_ = year;
    month_ = month;
    day_ = date;
  }

  void AddDay(int inc)
  {
    day_ += inc;
    while(day_ > everymonth[month_-1])
    {
        if(year_ / 4 == 0)
        everymonth[1] = 29;
        else
        everymonth[1] = 28;
        AddMonth(1);
        day_ -= everymonth[month_-1];
    }
  }

  void AddMonth(int inc)
  {
    month_ += inc;
    if(month_ > 12)
    {
        year_ += month_ / 12;
        month_ = month_ % 12;
    }
  }

  void AddYear(int inc)
  {
    year_ += inc;
  }

  void ShowDate()
  {
    std::cout << year_ << "." << month_ << "." << day_ << std::endl;
  }
};

int main()
{
    Date day;
    day.SetDate(2022, 1, 10);
    day.ShowDate();

    day.AddYear(1);
    day.ShowDate();

    day.AddMonth(13);
    day.ShowDate();

    day.AddDay(1600);
    day.ShowDate();
}