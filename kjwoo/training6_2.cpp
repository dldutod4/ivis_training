#include <iostream>
#include <string>

class Base
{
    std::string s;

public:
    Base() : s("기반") { std::cout << "기반 클래스" << std::endl; }

    virtual void what() { std::cout << s << std::endl; }                                                   
    //virtual 업캐스팅시 객체의 클래스를 확인해서 해당 클래스 멤버함수를 호출 
    //런타임 시에 결정되기때문에 동적바인딩이라고 한다.
};
class Derived : public Base
{
    std::string s;

public:
    Derived() : s("파생"), Base() { std::cout << "파생 클래스" << std::endl; }

    void what() override { std::cout << s << std::endl; } 
    //제대로 오버라이드 되었는지 컴파일 타임에 확인하기위해 override 키워드 사용
};
int main()
{
    Base p;
    Derived c;

    std::cout << "=== 포인터 버전 ===" << std::endl;
    Base *p_c = &c; // 업캐스팅 -> derived is a base이기 때문에 캐스팅해도 무방.
    Base *p_x = &p;
    // Derived* p_p = &p;  //컴파일 오류
    Derived *p_p = static_cast<Derived *>(p_c); // 원래 derived였던 객체이기때문에 다운캐스팅이 가능하다.

    p_c->what(); //-> 업캐스팅을 하면 오버라이딩된 함수가 아닌 기반클래스의 함수가 실행
    // 강제적인 다운캐스팅을 하는 경우 런타임오류가 발생하기때문에 작동이 보장되지않는한 매우 권장하지않음.
    // 캐스팅 오류를 방지하기위해 dynamic cast를 사용 가능. 상속간의 포인터들의 캐스팅을 해줌.

    // Derived* p_y = dynamic_cast<Derived*>(p_x); // 컴파일 오류 발생
    Derived *p_z = static_cast<Derived *>(p_x); // 컴파일 오류 발생 x (오류 찾기가 매우 힘듦)

    //업캐스팅을 한 경우에도 본래 클래스의 멤버함수를 실행 하고 싶을 때 --> virtual 키워드 사용
    //

    return 0;
}