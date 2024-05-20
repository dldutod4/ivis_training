/*
const static

*/
#include <iostream>
class Marine
{
    static int total_marine_num; // 자동으로 0으로 초기화 클래스가 공유하는 변수
    int hp;
    int coord_x, coord_y;
    int damage;
    int is_dead;

public:
    
    Marine();
    Marine(int x, int y);
    Marine(const Marine& cp);

    int attack() const; // const함수 - 다른 변수를 변경시키지않는 변수 - 읽기만 가능 + 다른 상수함수만 호출가능
    Marine &be_attacked(int damage_earn);
    void move(int x, int y);
    void show_status();
    static void show_total_marine();
};
/* 초기화 리스트를 사용하는 이유 - 생성과 초기화를 동시에 함.

사용하지 않는 경우 생성 후 대입을 수행
전자가 더 효율적 +
상수나 레퍼런스들은 생성과 동시에 초기화되어야함. 따라서 초기화 리스트를 사용해 초기화 해야함

*/
Marine::Marine() : hp(50), coord_x(0), coord_y(0), damage(5), is_dead(false) {}
Marine::Marine(int x, int y)
    : coord_x(x), coord_y(y), hp(50), damage(5), is_dead(false) {}
Marine::Marine(const Marine& cp)
{
}

void Marine::move(int x, int y)
{
    coord_x = x;
    coord_y = y;
}
void Marine::show_total_marine() //static 함수 - 객체를 생성하지 않아도 사용가능
{
    std::cout << "전체 마린 수 : " << total_marine_num << std::endl;
}

int Marine::attack() const { return damage; }
/*
레퍼런스를 리턴하는 멤버함수
this는 객체 자신을 가리키는 포인터
return this*은 객체 자신을 리턴하는 것

만약 리턴타입이 레퍼런스 타입이 아닌경우
임시객체를 생성해 복사된 것이 반환되는 반면
레퍼런스 타입인경우 그 자체가 반환됨
m1.be_attacked(10).be_attacked(20); 이 가능

////////////////////////////////////////////////////////
레퍼런스타입을 반환했을 때 레퍼런스로 받는것과 레퍼런스가 아닌 타입으로 받는것이 다름
int x;
int& fnc(){
    return x;
}
x의 레퍼런스가 반환되어 x의 값이 아닌 멤버변수 x자체가 반환됨.
int& a= m1.fnc(); //a를 m1.x처럼 사용가능
int a= m1.fnc(); //a에 m1.x의 값이 복사

/////////////////////////////////////////////////////////
int x;
int fnc(){
    return x;
}
int &a = m1.fnc(); // 컴파일오류 - 반환되는 x는 복사된 임시 객체 int이므로 소멸되기때문에
a 는 없는 변수를 참조하게되기 때문

*/
Marine &Marine::be_attacked(int damage_earn)
{
    this->hp -= damage_earn;
    if (this->hp <= 0)
        this->is_dead = true;

    return *this;
}
void Marine::show_status()
{
    std::cout << " *** Marine *** " << std::endl;
    std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
              << std::endl;
    std::cout << " HP : " << hp << std::endl;
}

int main()
{
    Marine marine1(2, 3);
    Marine marine2(3, 5);

    marine2 = marine1;
    marine1.be_attacked(10);

    marine1.show_status();
    marine2.show_status();
    //Marine::show_total_marine();

}

//Q1
/*

#include <iostream>

class A {
  int x;

 public:
  A(int c) : x(c) {}
  A(const A& a) {
    x = a.x;
    std::cout << "복사 생성" << std::endl;
  }
};

class B {
  A a;

 public:
  B(int c) : a(c) {}
  B(const B& b) : a(b.a) {}
  A get_A() {
    A temp(a);
    return temp;
  }
};

int main() {
  B b(10);

  std::cout << "---------" << std::endl;
  A a1 = b.get_A(); //temp 가 임시객체로 복사되는 과정에서 한번 임시객체에서  a1으로 복사되는 과정에서 한번
  총 2회 발생하지만 copy elision에 의해 한번만 발생
}*/
