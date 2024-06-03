// 연산자 오버로딩
/*
c++에서는 사용자 정의 연산자를 사용가능
(리턴타입) operator(연산자) (연산자가 받는 인자)

bool MyString::operator==(MyString& str){
    return !compare(str);
}

str1 == str2
str1.operator==(str2)로 변환됨.

사칙연산시 리턴타입이 중요
class Num이 있을 때
Num& operator+ (const Num& n){
    num+=n.num;
    return *this;
}
이면 레퍼런스 반환으로 속도는 더 빨라지지만
b+a+b를 했을때
(b.+(a)).+(b)가 일어나므로
b에 a가 더해지게 돼어 +(b) 시에 사실상 a가 한번 더 더해진다
이런 결과를 막기위해 사칙연산시 리턴타입은 값을 반환하는 것이 좋다.

대입연산시 에는 레퍼런스를 반환하는 것이좋다.
불필요한 복사를 방지한다.
*/

#include <string.h>
#include <iostream>

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

    int length() const;
    int capacity() const;
    void reserve(int size);

    void print() const;
    void println() const;

    char at(int i) const;

    int compare(MyString &str);
    bool operator==(MyString &str);
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
int MyString::length() const { return string_length; }
void MyString::print() const
{
    for (int i = 0; i != string_length; i++)
        std::cout << string_content[i];
}
void MyString::println() const
{
    for (int i = 0; i != string_length; i++)
        std::cout << string_content[i];

    std::cout << std::endl;
}
int MyString::capacity() const { return memory_capacity; }
void MyString::reserve(int size)
{
    if (size > memory_capacity)
    {
        char *prev_string_content = string_content;

        string_content = new char[size];
        memory_capacity = size;

        for (int i = 0; i != string_length; i++)
            string_content[i] = prev_string_content[i];

        delete[] prev_string_content;
    }

    // 만일 예약하려는 size 가 현재 capacity 보다 작다면
    // 아무것도 안해도 된다.
}
char MyString::at(int i) const
{
    if (i >= string_length || i < 0)
        return 0;
    else
        return string_content[i];
}
int MyString::compare(MyString &str)
{
    // (*this) - (str) 을 수행해서 그 1, 0, -1 로 그 결과를 리턴한다
    // 1 은 (*this) 가 사전식으로 더 뒤에 온다는 의미. 0 은 두 문자열
    // 이 같다는 의미, -1 은 (*this) 사 사전식으러 더 앞에 온다는 의미이다.

    for (int i = 0; i < std::min(string_length, str.string_length); i++)
    {
        if (string_content[i] > str.string_content[i])
            return 1;

        else if (string_content[i] < str.string_content[i])
            return -1;
    }

    // 여기 까지 했는데 끝나지 않았다면 앞 부분 까지 모두 똑같은 것이 된다.
    // 만일 문자열 길이가 같다면 두 문자열은 아예 같은 문자열이 된다.

    if (string_length == str.string_length)
        return 0;

    // 참고로 abc 와 abcd 의 크기 비교는 abcd 가 더 뒤에 오게 된다.
    else if (string_length > str.string_length)
        return 1;

    return -1;
}
bool MyString::operator==(MyString &str)
{
    return !compare(str); // str 과 같으면 compare 에서 0 을 리턴한다.
}

class Complex
{
    double real, img;

public:
    Complex(double real, double img) : real(real), img(img) {}
    Complex(const char *str);

    Complex operator+(const Complex &c) const;
    Complex operator+(const char *c) const;
    Complex operator-(const Complex &c) const;
    Complex operator-(const char *c) const;
    Complex operator*(const Complex &c) const;
    Complex operator*(const char *c) const;
    Complex operator/(const Complex &c) const;
    Complex operator/(const char *c) const;
    Complex &operator=(const Complex &c);
    Complex &operator+=(const Complex &c);
    Complex &operator-=(const Complex &c);
    Complex &operator*=(const Complex &c);
    Complex &operator/=(const Complex &c);
    void show()
    {
        std::cout << real << "+" << img << "i" << std::endl;
    }
    double get_number(const char *str, int from, int to) const;
};
Complex Complex::operator+(const Complex &c) const
{
    Complex temp(real + c.real, img + c.img);
    return temp;
}
Complex Complex::operator-(const Complex &c) const
{
    Complex temp(real - c.real, img - c.img);
    return temp;
}
Complex Complex::operator*(const Complex &c) const
{
    Complex temp(real * c.real - img * c.img, real * c.img + img * c.real);
    return temp;
}
Complex Complex::operator/(const Complex &c) const
{
    Complex temp(
        (real * c.real + img * c.img) / (c.real * c.real + c.img * c.img),
        (img * c.real - real * c.img) / (c.real * c.real + c.img * c.img));
    return temp;
}
Complex &Complex::operator=(const Complex &c)
{ // 디폴트 대입연산자가 자동생성되긴 함
    real = c.real;
    img = c.img;
    return *this; // 동일 연산자 우선순위가 오른쪽부터 처리하기 때문에 자신을 반환해야 한다.
}
Complex &Complex::operator+=(const Complex &c)
{
    (*this) = (*this) + c;
    return *this;
}
Complex &Complex::operator-=(const Complex &c)
{
    (*this) = (*this) - c;
    return *this;
}
Complex &Complex::operator*=(const Complex &c)
{
    (*this) = (*this) * c;
    return *this;
}
Complex &Complex::operator/=(const Complex &c)
{
    (*this) = (*this) / c;
    return *this;
}
Complex::Complex(const char *str) //사실 이 생성자를 만들어주면 +-*/도 자동으로 가능해진다. 자체적으로 변환해서 사칙연산하기 때문 
//단 연산자 오버로딩시에 확실히 인자를 const로 받아야한다.
{
    // 입력 받은 문자열을 분석하여 real 부분과 img 부분을 찾아야 한다.
    // 문자열의 꼴은 다음과 같습니다 "[부호](실수부)(부호)i(허수부)"
    // 이 때 맨 앞의 부호는 생략 가능합니다. (생략시 + 라 가정)

    int begin = 0, end = strlen(str);
    img = 0.0;
    real = 0.0;

    // 먼저 가장 기준이 되는 'i' 의 위치를 찾는다.
    int pos_i = -1;
    for (int i = 0; i != end; i++)
    {
        if (str[i] == 'i')
        {
            pos_i = i;
            break;
        }
    }

    // 만일 'i' 가 없다면 이 수는 실수 뿐이다.
    if (pos_i == -1)
    {
        real = get_number(str, begin, end - 1);
        return;
    }

    // 만일 'i' 가 있다면,  실수부와 허수부를 나누어서 처리하면 된다.
    real = get_number(str, begin, pos_i - 1);
    img = get_number(str, pos_i + 1, end - 1);

    if (pos_i >= 1 && str[pos_i - 1] == '-')
        img *= -1.0;
}
Complex Complex::operator+(const char *str) const
{
    Complex temp(str);
    return (*this) + temp;
}
Complex Complex::operator-(const char *str) const
{
    Complex temp(str);
    return (*this) - temp;
}
Complex Complex::operator*(const char *str) const
{
    Complex temp(str);
    return (*this) * temp;
}
Complex Complex::operator/(const char *str) const
{
    Complex temp(str);
    return (*this) / temp;
}

double Complex::get_number(const char *str, int from, int to) const
{
    bool minus = false;
    if (from > to)
        return 0;
    if (str[from] == '-')
        minus = true;
    if (str[from] == '-' || str[from] == '+')
        from++; // 부호 붙였을때 다음자리부터 읽음.

    double num = 0.0;
    double decimal = 1.0;
    bool integer_part = true;
    for (int i = from; i <= to; i++)
    {
        if (isdigit(str[i]) && integer_part)
        {
            num *= 10.0;
            num += (str[i] - '0');
        }
        else if (str[i] == '.')
            integer_part = false;
        else if (isdigit(str[i]) && !integer_part)
        {
            decimal /= 10.0;
            num += ((str[i] - '0') * decimal);
        }
        else
            break;
    }
    if (minus) num *= -1.0;

    return num;
}
int main()
{
    MyString str1("a word");
    MyString str2("sentence");
    MyString str3("sentence");

    if (str1 == str2)
        std::cout << "str1 와 str2 같다." << std::endl;
    else
        std::cout << "st1 와 str2 는 다르다." << std::endl;

    if (str2 == str3)
        std::cout << "str2 와 str3 는 같다." << std::endl;
    else
        std::cout << "st2 와 str3 는 다르다" << std::endl;

    Complex num1(1, 3);
    Complex num2(2, 4);
    Complex num3 = num1 + num2;
    Complex num4 = num1 / num2;
    num3.show();
    num4.show();
    num1 = num2 = num3; // num1.=(num2.=(num3)) 동일 연산시 우측부터 처리
    // n1 =a n2= b n3=c였을때
    // n1 n2 n3 = c가된다.
    num1.show();
    num2.show();
    num3.show();
}