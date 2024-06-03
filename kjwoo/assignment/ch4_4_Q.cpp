// 문제 1

//     아래와 같은 코드에서 복사 생성 은 몇 번 이나 표시될까요
//     ?

// #include <iostream>

//     class A
// {
//     int x;

// public:
//     A(int c) : x(c) {}
//     A(const A &a)
//     {
//         x = a.x;
//         std::cout << "복사 생성" << std::endl;
//     }
// };

// class B
// {
//     A a;

// public:
//     B(int c) : a(c) {}
//     B(const B &b) : a(b.a) {}
//     A get_A()
//     {
//         A temp(a);
//         return temp;
//     }
// };

// int main()
// {
//     B b(10);

//     std::cout << "---------" << std::endl;
//     A a1 = b.get_A();
// }
// temp 가 임시객체로 복사되는 과정에서 한번 임시객체에서  a1으로 복사되는 과정에서 한번
//  총 2회 발생하지만 copy elision에 의해 한번만 발생 http://en.wikipedia.org/wiki/Copy_elision 참조
