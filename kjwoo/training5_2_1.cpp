
/*
첨자 연산자.
[]안에 넣는수를 첨자라고 부름 (subscript)
char& MyString::operator[](const int index) { return string_content[index]; }

int Wrapper 클래스 - 타입 변환 연산자
Wrapper  기본자료형을 객체로 다룰 때 사용.

class Int
{
  int data;
  // some other data

 public:
  Int(int data) : data(data) {}
  Int(const Int& i) : data(i.data) {}
};

//일일이 int의 operator와 같은 동작을 하는 함수를 오버로딩하는 건 너무 비효율적
타입 변환 연산자
operator (변환타입)() 으로 정의
ex) operator int() {return data}
이러면 operator 연산시 int로 변환해 처리.

전위/후위 증감연산자
a++와 ++a 구분.

operator++() //전위
operator++(int) //후위
int는 아무의미없이 구분을 하기위해 존재함. 인수의 이름조차 정할필요 없음.
단 전위 연산의 경우 값이 바뀐 자신을 리턴하고
후위연산흔 값이 바뀌기 전의 객체를 리턴해야함.

A& operator++() { //전위
  // A ++ 을 수행한다.
  return *this;
}

A operator++(int) { //후위 즉 복사생성자 호출로 인해 더 느림
  A temp(A);
  // A++ 을 수행한다.
  return temp;
}
*/
#include <iostream>
#include <cstring>

class MyString
{
    char *string_content; // 문자열 데이터를 가리키는 포인터
    int string_length;    // 문자열 길이

    int memory_capacity; // 현재 할당된 용량

public:
    // 문자 하나로 생성
    MyString(char c);

    // 문자열로 부터 생성
    MyString(const char *str);

    // 복사 생성자
    MyString(const MyString &str);

    ~MyString();

    int length();

    void print() const;
    void println() const;

    char &operator[](const int index);
};

MyString::MyString(char c)
{
    string_content = new char[1];
    string_content[0] = c;
    memory_capacity = 1;
    string_length = 1;
}
MyString::MyString(const char *str)
{
    string_length = strlen(str);
    memory_capacity = string_length;
    string_content = new char[string_length];

    for (int i = 0; i != string_length; i++)
        string_content[i] = str[i];
}
MyString::MyString(const MyString &str)
{
    string_length = str.string_length;
    string_content = new char[string_length];

    for (int i = 0; i != string_length; i++)
        string_content[i] = str.string_content[i];
}
MyString::~MyString() { delete[] string_content; }
int MyString::length() { return string_length; }
void MyString::print() const
{
    for (int i = 0; i != string_length; i++)
    {
        std::cout << string_content[i];
    }
}
void MyString::println() const
{
    for (int i = 0; i != string_length; i++)
    {
        std::cout << string_content[i];
    }
    std::cout << std::endl;
}

char &MyString::operator[](const int index) { return string_content[index]; }

int main()
{
    MyString str("abcdef");
    str[3] = 'c';

    str.println();
}