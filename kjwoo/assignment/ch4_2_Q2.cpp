// // 문제 2 
// // 수학 관련 소프트웨어를 만드는 회사에서 의뢰가 들어왔습니다.
// // 중학생용 기하학 소프트웨워를 만드는 것인데요, 
// // 클래스는 총 두 개로 하나는 Point 로 점에 관한 정보를 담는 것이고 
// // 다른 하나는 Geometry 로 점들을 가지고 연산을 하는 클래스 입니다.
// // 즉 아래와 같은 두 클래스의 함수들을 모두 정의하세요(난이도 : 上)
// class Point {
//   int x, y;

//  public:
//   Point(int pos_x, int pos_y);
// };

// class Geometry {
//  public:
//   Geometry() {
//     num_points = 0;
//   }

//   void AddPoint(const Point &point) {
//     point_array[num_points ++] = new Point(point.x, point.y);
//   }

//   // 모든 점들 간의 거리를 출력하는 함수 입니다.
//   void PrintDistance();

//   // 모든 점들을 잇는 직선들 간의 교점의 수를 출력해주는 함수 입니다.
//   // 참고적으로 임의의 두 점을 잇는 직선의 방정식을 f(x,y) = ax+by+c = 0
//   // 이라고 할 때 임의의 다른 두 점 (x1, y1) 과 (x2, y2) 가 f(x,y)=0 을 기준으로
//   // 서로 다른 부분에 있을 조건은 f(x1, y1) * f(x2, y2) <= 0 이면 됩니다.
//   void PrintNumMeets();

// private:
//   // 점 100 개를 보관하는 배열.
//   Point* point_array[100];
//   int num_points;
// };

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