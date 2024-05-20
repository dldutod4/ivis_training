#include <iostream>

class Parent
{
public:
    Parent() { std::cout << "Parent 생성자 호출" << std::endl; }
    //~Parent() { std::cout << "Parent 소멸자 호출" << std::endl; }
    virtual ~Parent() { std::cout << "Parent 소멸자 호출" << std::endl; } // child 소멸자도 실행
};
class Child : public Parent
{
public:
    Child() : Parent() { std::cout << "Child 생성자 호출" << std::endl; }
    ~Child() { std::cout << "Child 소멸자 호출" << std::endl; } // child소멸자가 알아서 parent소멸자도 같이 실행한다.
};

class A
{
public:
    virtual void show() { std::cout << "Parent !" << std::endl; }
};
class B : public A
{
public:
    void show() override { std::cout << "Child!" << std::endl; }
};

//추상클래스의 객체는 생성이 안되지만 포인터는 생성가능하다.
class Animal {
 public:
  Animal() {}
  virtual ~Animal() {}
  virtual void speak() = 0; //pure virtual 함수 = 반드시 오버라이딩 돼야하는 함수
  // 또한 Animal객체는 만들 수 없음. (추상 클래스)
};

class Dog : public Animal {
 public:
  Dog() : Animal() {}
  void speak() override { std::cout << "왈왈" << std::endl; }
};

class Cat : public Animal {
 public:
  Cat() : Animal() {}
  void speak() override { std::cout << "야옹야옹" << std::endl; }
};

void test(A &a) { a.show(); }

int main()
{
    std::cout << "--- 평범한 Child 만들었을 때 ---" << std::endl;
    {
        Child c;
    }
    std::cout << "--- Parent 포인터로 Child 가리켰을 때 ---" << std::endl;
    {
        Parent *p = new Child(); // 업캐스팅시 원래 클래스의 소멸자가 호출되지않음.
        delete p;
    }
    A a;
    B b;
    test(a); 
    test(b); //A객체로 업캐스팅 되었지만 virtual 덕분에 B::show()가 실행됨.
}

//virtual이 디폴트가 아닌 이유 -> 약간의 오버헤드가 발생하기 때문.

//다중상속
class C : public B, public A{
     C() : A(), B() { std::cout << "C 생성자 호출" << std::endl; } //생성자는 상속순서에 따라서 호출된다.
     //즉 B A C 순서로 호출된다. 명시된 순서는 상관이 없다.
};

//다이아몬드 상속 (주의)
class Human {
  // ...
};
class HandsomeHuman : public virtual Human {
  // ...
};
class SmartHuman : public virtual Human {
  // ...
};
class Me : public HandsomeHuman, public SmartHuman {
  // ...
};

//위와 같은경우 Me는 Human을 두번 상속받게된다. 
//이때 Human을 virtual로 상속받으면 한번만 포함하도록 지정하게된다.