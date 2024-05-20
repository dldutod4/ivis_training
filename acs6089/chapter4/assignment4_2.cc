#include <iostream>
#include <cmath>

class Point {
 public:
  int x, y;
  Point(int pos_x, int pos_y)
  {
    x = pos_x;
    y = pos_y;
  }
};

class Geometry {
 public:
  Geometry() {
    num_points = 0;
  }

  void AddPoint(const Point &point) {
    point_array[num_points ++] = new Point(point.x, point.y);
  }

  // 모든 점들 간의 거리를 출력하는 함수 입니다.
  void PrintDistance()
  {
    if(num_points >= 2)
    {
        int lines = 0;
        for (size_t i = 0; i < num_points-1; i++)
        {
            for (size_t j = i + 1; j < num_points; j++)
            {
                std::cout << sqrt(pow(point_array[i]->x - point_array[j]->x, 2) + pow(point_array[i]->y - point_array[j]->y, 2)) << std::endl;
                lines++;
            }
        }
        std::cout << "total lines : " << lines << std::endl;
    }
    else
    {
        std::cout << "you have " << num_points << "point only. please input more point than 2" << std::endl;
    }
  }

  // 모든 점들을 잇는 직선들 간의 교점의 수를 출력해주는 함수 입니다.
  // 참고적으로 임의의 두 점을 잇는 직선의 방정식을 f(x,y) = ax+by+c = 0
  // 이라고 할 때 임의의 다른 두 점 (x1, y1) 과 (x2, y2) 가 f(x,y)=0 을 기준으로
  // 서로 다른 부분에 있을 조건은 f(x1, y1) * f(x2, y2) <= 0 이면 됩니다.
  void PrintNumMeets()
  {
    if(num_points >= 4)
    {
      int meet_point = 0;
      for (size_t i = 0; i < num_points-3; i++)
      {
        for (size_t j = i+1; j < num_points-2; j++)
        {
          double sloop1;
          sloop1 = (double)(point_array[j]->y - point_array[i]->y)/(point_array[j]->x -point_array[i]->x);
          for (size_t k = j+1; k < num_points-1; k++)
          {
            for (size_t l = k+1; l < num_points; l++)
            {
              //meet_point += PointsNumMeets(point_array[i], b, c, d);
              if(sloop1 != (double)(point_array[l]->y - point_array[k]->y)/(point_array[l]->x - point_array[k]->x))meet_point++;
            }
          }
        }
      }

      //여러 점 중 3개의 점을 선택하여 직선을 연결하면 무조건 3개의 교점이 생긴다.
      meet_point += (int)(num_points * (num_points-1) * (num_points-2) / 2);
      
      std::cout << "meet point : " << meet_point << std::endl;
    }
    else
    {
        std::cout << "you have " << num_points << "points only. please input more point than 4" << std::endl;
    }
  }

  int PointsNumMeets(const Point &a, const Point &b, const Point &c, const Point &d)
  {
    int meets = 0;
    return meets;
  }

private:
  // 점 100 개를 보관하는 배열.
  Point* point_array[100];
  int num_points;
};

int main()
{
    Geometry geo = Geometry();
    geo.AddPoint(Point(1,1));
    geo.AddPoint(Point(2,2));
    geo.AddPoint(Point(2,1));
    geo.AddPoint(Point(1,2));

    geo.PrintDistance();
    geo.PrintNumMeets();

    return 0;
}