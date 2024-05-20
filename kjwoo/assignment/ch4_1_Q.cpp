// 문제 1

//     여러분은 아래와 같은 Date 클래스를 디자인 하려고 합니다.
//     SetDate 는 말그대로 Date 함수 내부를 초기화 하는 것이고
//     AddDay,AddMonth, AddYear 는 일, 월, 년을 원하는 만큼 더하게 됩니다.
//     한 가지 주의할 점은 만일 2012 년 2 월 28 일에 3 일을 더하면
//     2012 년 2 월 31 일이 되는 것이 아니라 2012 년 3 월 2 일이 되겠지요 ? (난이도 : 上)

#include <iostream>
class Date
{
    int year_;
    int month_; // 1 부터 12 까지.
    int day_;   // 1 부터 31 까지.

public:
    void SetDate(int year, int month, int date)
    {
        year_ = year;
        month_ = month;
        day_ = date;
    };

    void AddDay(int inc)
    {
        day_ += inc;
        while (day_ > 31)
        {
            day_ -= 31;
            AddMonth(1);
        }
    };
    void AddMonth(int inc)
    {
        month_ += inc;
        while (month_ > 12)
        {
            month_ -= 12;
            AddYear(1);
        }
    };
    void AddYear(int inc)
    {
        year_ += inc;
    };

    void ShowDate()
    {
        std::cout << year_ << "년" << month_ << "월" << day_ << "일" << std::endl;
    };
};

int main()
{
    Date today;
    int input;
    int input1, input2;
    while (1)
    {
        std::cout << "0:초기화 1:수정 2:출력. 입력:";
        std::cin >> input;
        if (input == 0)
        {
            today.SetDate(2000, 1, 1);
        }
        else if (input == 1)
        {

            std::cout << "0:일 1:월 2:년 입력:";
            std::cin >> input1;
            std::cout << "증가량 입력:";
            std::cin >> input2;
            if (input1 == 0)
            {
                today.AddDay(input2);
            }
            else if (input1 == 1)
            {
                today.AddMonth(input2);
            }
            else
            {
                today.AddYear(input2);
            }
        }
        else if (input == 2)
        {
            today.ShowDate();
        }
        else
            break;
    }
}