/*
 함수 오버로딩
 cpp에서는 같은 이름함수가 여러개여도 된다.

void print(int x) { std::cout << "int : " << x << std::endl; }
void print(char x) { std::cout << "char : " << x << std::endl; }
void print(double x) { std::cout << "double : " << x << std::endl; }
인자가 다르면 다른 함수

fnc(int) fnc(double)이 있을 때
자신과 최대로 근접한 함수를 찾아 실행
1. 정확히 일치
2. 형변환
char, unsigned char, short -> int
unsigned short -> int or unsigned int (크기에 따라 다름)
float -> double
Enum -> int
3.포괄적 형변환
숫자는 다른 숫자타입으로 변환 ex float->int
enum -> double
0 -> 포인터 or 숫자
포인터 -> void
4. 유저 정의 타입

같은단계에서 2개이상이 일치하면 오류 (ambiguous)

// */
// #include <iostream>

// class Date
// {
//     int year_;
//     int month_; // 1 부터 12 까지.
//     int day_;   // 1 부터 31 까지.

// public:
//     void SetDate(int year, int month, int date);
//     void AddDay(int inc);
//     void AddMonth(int inc);
//     void AddYear(int inc);

//     // 해당 월의 총 일 수를 구한다.
//     int GetCurrentMonthTotalDays(int year, int month);

//     void ShowDate();
//     Date() = default; //기본생성자 지시해서 생성가능 - 생성자가 아예없어도 생성.
//     Date(int year, int month, int day)
//     { // 생성자 리턴값이 없다.
//         year_ = year;
//         month_ = month;
//         day_ = day;
//     }
//     Date(int year){
//         year_= year;
//         month_=1;
//         day_=1;
//     }
// };

// void Date::SetDate(int year, int month, int day) // 클래스이름::으로 클래스 밖에서 정의 가능
// {
//     year_ = year;
//     month_ = month;
//     day_ = day;
// }

// int Date::GetCurrentMonthTotalDays(int year, int month)
// {
//     static int month_day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//     if (month != 2)
//     {
//         return month_day[month - 1];
//     }
//     else if (year % 4 == 0 && year % 100 != 0)
//     {
//         return 29; // 윤년
//     }
//     else
//     {
//         return 28;
//     }
// }

// void Date::AddDay(int inc)
// {
//     while (true)
//     {
//         // 현재 달의 총 일 수
//         int current_month_total_days = GetCurrentMonthTotalDays(year_, month_);

//         // 같은 달 안에 들어온다면;
//         if (day_ + inc <= current_month_total_days)
//         {
//             day_ += inc;
//             return;
//         }
//         else
//         {
//             // 다음달로 넘어가야 한다.
//             inc -= (current_month_total_days - day_ + 1);
//             day_ = 1;
//             AddMonth(1);
//         }
//     }
// }

// void Date::AddMonth(int inc)
// {
//     AddYear((inc + month_ - 1) / 12);
//     month_ = month_ + inc % 12;
//     month_ = (month_ == 12 ? 12 : month_ % 12);
// }

// void Date::AddYear(int inc) { year_ += inc; }

// void Date::ShowDate()
// {
//     std::cout << "오늘은 " << year_ << " 년 " << month_ << " 월 " << day_
//               << " 일 입니다 " << std::endl;
// }

// int main()
// {
//     // Date day;
//     // day.SetDate(2011, 3, 1);
//     // day.ShowDate();

//     // day.AddDay(30);
//     // day.ShowDate();

//     // day.AddDay(2000);
//     // day.ShowDate();

//     // day.SetDate(2012, 1, 31); // 윤년
//     // day.AddDay(29);
//     // day.ShowDate();

//     // day.SetDate(2012, 8, 4);
//     // day.AddDay(2500);
//     // day.ShowDate();
//     // return 0;

//     Date day(2011, 3, 1);
//     day.ShowDate();

//     day.AddYear(10);
//     day.ShowDate();

//     return 0;
// }
#include <iostream>
#include <math.h>
class Point
{
public:
    int x, y;
    Point(int pos_x, int pos_y);
};
Point::Point(int pos_x, int pos_y)
{
    x = pos_x;
    y = pos_y;
};

class Line
{ // 라인 클래스 추가
private:
public:
    Point *p1_;
    Point *p2_;
    Line(Point *p1, Point *p2)
    {
        p1_ = p1;
        p2_ = p2;
    }
};
class Geometry
{
public:
    Geometry()
    {
        num_points = 0;
        num_lines = 0;
    }

    void AddPoint(const Point &point)
    {
        point_array[num_points] = new Point(point.x, point.y);
        if (num_points > 1)
        {                                        // 점 2개이상 부터 line 추가
            for (int i = 0; i < num_points; i++) // 새로들어온 점과 이전점들로 라인 생성
            {
                AddLine(point_array[i], point_array[num_points]);
            }
        }
        num_points++;
    }
    void AddLine(Point *p1, Point *p2)
    {
        line_array[num_lines++] = new Line(p1, p2);
    }

    bool isMeet(Line *l1, Line *l2)
    {
        // l1의 직선의 방정식 ax+by+c = 0
        int x1, x2, y1, y2;
        x1 = l1->p1_->x;
        x2 = l1->p2_->x;
        y1 = l1->p1_->y;
        y2 = l1->p2_->y;

        double a, b, c;

        if (x1 == x2)
        { // 기울기가 무한인 경우
            a = 1;
            b = 0;
            c = x1;
        }
        else
        { //
            a = (y2 - y1) / (x2 - x1);
            b = -1;
            c = y1 - (a * x1);
        }

        // l2의 직선과 비교
        x1 = l2->p1_->x;
        x2 = l2->p2_->x;
        y1 = l2->p1_->y;
        y2 = l2->p2_->y;

        // 교점 확인

        if ((a * x1 + b * y1 + c) * (a * x2 + b * y2 + c) <= 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // 모든 점들 간의 거리를 출력하는 함수 입니다.
    void PrintDistance();

    // 모든 점들을 잇는 직선들 간의 교점의 수를 출력해주는 함수 입니다.
    // 참고적으로 임의의 두 점을 잇는 직선의 방정식을 f(x,y) = ax+by+c = 0
    // 이라고 할 때 임의의 다른 두 점 (x1, y1) 과 (x2, y2) 가 f(x,y)=0 을 기준으로
    // 서로 다른 부분에 있을 조건은 f(x1, y1) * f(x2, y2) <= 0 이면 됩니다.
    void PrintNumMeets();

private:
    // 점 100 개를 보관하는 배열.
    Point *point_array[100];
    Line *line_array[10000];
    int num_points;
    int num_lines;
};
void Geometry::PrintDistance()
{
    for (int i = 0; i < num_points; i++)
    {
        for (int j = 0; j < num_points; j++)
        {
            if (i != j)
            {
                double dist =
                    sqrt(
                        pow(point_array[i]->x - point_array[j]->x, 2) +
                        pow(point_array[i]->y - point_array[j]->y, 2));

                std::cout << dist << std::endl;
            }
        }
    }
}
/*
 */
void Geometry::PrintNumMeets()
{
    int totalMeets = 0;
    for (int i = 0; i < num_lines - 1; i++)
    { // 한 직선 선택
        for (int j = i + 1; j < num_lines; j++)
        { // 다른 직선 선택
            if (isMeet(line_array[i], line_array[j]))
            {
                totalMeets++;
            }
        }
    }
    std::cout << "교점의 수:" << totalMeets << std::endl;
}

int main()
{
    int x, y;
    Geometry g = Geometry();
    for (int i = 0; i < 3; i++)
    {
        std::cin >> x >> y;
        g.AddPoint(*(new Point(x, y)));
    }

    g.PrintDistance();
    g.PrintNumMeets();
}