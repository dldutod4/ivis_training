#include <iostream>

class string {
  char *str;
  int len;

 public:
  string(char c, int n);  // 문자 c 가 n 개 있는 문자열로 정의
  string(const char *s);
  string(const string &s);
  ~string(){if(str)delete[] str;};

  void show_string();
  void add_string(const string &s);   // str 뒤에 s 를 붙인다.
  void copy_string(const string &s);  // str 에 s 를 복사한다.
  int strlen(){return len;}           // 문자열 길이 리턴
};

string::string(char c, int n)
{
  str = new char[n];
  for (size_t i = 0; i < n; i++)
  {
    str[i] = c;
  }
  str[n] = '\0';
  len = n;
}

string::string(const char *s)
{
  len = 0;
  while(s[len] != '\0')
  {
    len++;
  }
  str = new char[len];
  for (size_t i = 0; i < len; i++)
  {
    str[i] = s[i];
  }
  str[len] = '\0';
}

string::string(const string &s)
{
  len = s.len;
  str = new char[len];
  for (size_t i = 0; i < len; i++)
  {
    str[i] = s.str[i];
  }
  str[len] = '\0';
}

void string::show_string()
{
  std::cout << len << ' ' << str << std::endl;
}

void string::add_string(const string &s)
{
  for (size_t i = 0; i < s.len; i++)
  {
    str[i+len] = s.str[i]; 
  }
  len += s.len;
  str[len] = '\0';
}

void string::copy_string(const string &s)
{
  for (size_t i = 0; i < s.len; i++)
  {
    str[i] = s.str[i];
  }
  len = s.len;
  str[len] = '\0';
}

int main()
{
  string s1('a', 4);
  s1.show_string();

  string s2("hello");
  s2.show_string();

  string s3(s2);
  s3.show_string();

  s3.add_string(s1);
  s3.show_string();

  s2.copy_string(s3);
  s2.show_string();

  return 0;
}