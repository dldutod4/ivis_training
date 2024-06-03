/*
explicit
mutable
암시적 변환
객체를 인자로 받는 함수가 있을때
다른 타입의 객체를 인자로 입력하면
입력한 인자로 받았어야할 객체로 변환 가능한지 확인하고
변환 가능하면 변환해서 넣어준다.
즉
void fnc(String s)에
fnc("abc")를 넣으면
"abc"를 String으로 변환할 방법을 찾는다
String 클래스에 String(const char* str)이라는 생성자가 있었다면 
"abc"를 인자로 String 객체를 생성해 인자로 전달한다.

그러나 암시적변환을 원하지 않는 경우도 있으므로 암시적변환을 막는 키워드가 explicit이다.
생성자에 explicit 키워드를 달아두면 그 생성자로는 암시적변환을 하지 않는다.
복사생성자로도 호출되는 것을 막는다.

mutable
mutable 멤버변수는 const 멤버함수에서도 변경이 가능하다.
mutable이 필요한 이유>
const는 객체 내부를 변경하지않는다는 의미이지만
실제로는 읽기를 위한 함수여도 내부에서 변경이 일어나고 사용자관점에서 명시하기위해 const를 붙여야할 때도 있다
이럴 때 예외적으로 변경할수있게 해주는 것이 mutable이다.

*/
#include <iostream>

class MyString
{
    char *string_content; // 문자열 데이터를 가리키는 포인터
    int string_length;    // 문자열 길이

    int memory_capacity;

public:
    // capacity 만큼 미리 할당함.
    explicit MyString(int capacity);

    // 문자열로 부터 생성
    MyString(const char *str);

    // 복사 생성자
    explicit MyString(const MyString &str);

    ~MyString();

    int length() const;
};

MyString::MyString(int capacity)
{
    string_content = new char[capacity];
    string_length = 0;
    memory_capacity = capacity;
    std::cout << "Capacity : " << capacity << std::endl;
}

MyString::MyString(const char *str)
{
    string_length = 0;
    while (str[string_length++])
    {
    }

    string_content = new char[string_length];
    memory_capacity = string_length;

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
int MyString::length() const { return string_length; }
void doSomething(MyString a){
    return;
}

int main() 
{ 
    MyString s(3); 
    MyString *s2 = new MyString("abc{");
    //MyString s3 = 5; //복사생성자도 호출이 불가함.
    //doSomething(4); //암시적 변환 금지.
}
