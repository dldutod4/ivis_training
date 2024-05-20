/*
객체란
인스턴스 변수와 인스턴스 함수를 가짐
인스턴스 함수로만 인스턴스 변수에 접근이 가능
-> 캡슐화

클래스
객체의 설계도
클래스 상에서는 멤버변수와 멤버함수라고 지칭 ->실재하는 것이 아님


*/
// #include <iostream>
// class Animal{
//     private: //키워드를 명시하지않아도 기본적으로 private으로 설정된다.
//         int food;
//         int weight;
//     public:
//         void set_animal(int _food, int _weight){
//             food = _food;
//             weight = _weight;
//         }
//         void increase_food(int inc){
//             food+=inc;
//             weight+=(inc/3);
//         }
//         void view_stat(){
//             std::cout << "이 동물의 food   : " << food << std::endl;
//             std::cout << "이 동물의 weight : " << weight << std::endl;
//         }

// };

#include <iostream>
class Date {
  int year_;
  int month_;  // 1 부터 12 까지.
  int day_;    // 1 부터 31 까지.

 public:
  void SetDate(int year, int month, int date){
    year_=year;
    month_=month;
    day_=date;
  };

  void AddDay(int inc){
    day_+=inc;
    while(day_ > 31){
        day_ -= 31;
        AddMonth(1);
    }
    
  };
  void AddMonth(int inc){
    month_+=inc;
    while(month_ > 12){
        month_-=12;
        AddYear(1);
    }
  };
  void AddYear(int inc){
    year_+=inc;
  };

  void ShowDate(){
    std::cout << year_ << "년" << month_<<"월" <<day_<<"일"<<std::endl;
  };
};

int main(){
    Date today;
    int input;
    int input1,input2;
    while(1){
        std::cout <<"0:초기화 1:수정 2:출력. 입력:";
        std::cin >> input;
        if(input==0){
            today.SetDate(2000,1,1);
        }
        else if(input == 1){

            std::cout <<"0:일 1:월 2:년 입력:";
            std::cin >> input1;
            std::cout <<"증가량 입력:";
            std::cin >> input2;
            if(input1 == 0){
                today.AddDay(input2);
            }
            else if(input1 == 1){
                today.AddMonth(input2);
            }
            else{
                today.AddYear(input2);
            }

        }
        else if(input == 2){
            today.ShowDate();

        }
        else break;
    }
}