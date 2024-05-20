// 문제 1

//     아래와 같은 문자열 클래스를
//     완성해보세요(난이도 : 中)

//         class string
// {
//     char *str;
//     int len;

// public:
//     string(char c, int n); // 문자 c 가 n 개 있는 문자열로 정의
//     string(const char *s);
//     string(const string &s);
//     ~string();

//     void add_string(const string &s);  // str 뒤에 s 를 붙인다.
//     void copy_string(const string &s); // str 에 s 를 복사한다.
//     int strlen();                      // 문자열 길이 리턴
// };

#include <iostream>
#include <string.h>

class string
{
    char *str;
    int len;

public:
    string(char c, int n); // 문자 c 가 n 개 있는 문자열로 정의
    string(const char *s);
    string(const string &s);
    ~string();

    void add_string(const string &s);  // str 뒤에 s 를 붙인다.
    void copy_string(const string &s); // str 에 s 를 복사한다.
    int strlen();                      // 문자열 길이 리턴
    void show();
};

string::string(char c, int n)
{
    str = new char[n + 1];
    for (int i = 0; i < n; i++)
    {
        str[i] = c;
    }
    str[n] = '\0';
    len = n;
}
string::string(const char *s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    str = new char[i];
    strcpy(str, s);
    len = i;
}
string::string(const string &s)
{
    len = s.len;
    str = new char[len + 1];

    strcpy(str, s.str);
}
string::~string()
{
    if (str)
        delete[] str;
}

void string::add_string(const string &s)
{
    char *tmp = str;
    str = new char[len + s.len + 1];
    strcpy(str, tmp);
    strcpy(str + len, s.str);
    len += s.len;
}
void string::copy_string(const string &s)
{
    len = s.len;
    str = new char[len + 1];
    strcpy(str, s.str);
}
int string::strlen()
{
    return len;
}
void string::show()
{
    std::cout << str << std::endl;
}
int main()
{
    string s1("hello");
    string s2 = s1;
    string s4('a', 10);
    s2.add_string(" world");
    s2.show();

    string s3("good");
    s3.copy_string(s2);
    s3.show();
    s4.show();

    std::cout << s1.strlen() << std::endl;
    std::cout << s2.strlen() << std::endl;
    std::cout << s3.strlen() << std::endl;
    std::cout << s4.strlen() << std::endl;
}