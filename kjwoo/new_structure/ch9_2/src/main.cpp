
#include <cstring>
#include <iostream>
#include <string>

size_t GetStringSize(const char *s) { return strlen(s); }

size_t GetStringSize(const std::string &s) { return s.size(); }

template <typename String, typename... Strings>
size_t GetStringSize(const String &s, Strings... strs)
{ // 인자로 받은 스트링들의 길이 합을 구한다.
    return GetStringSize(s) + GetStringSize(strs...);
}

void AppendToString(std::string *concat_str) { return; }

template <typename String, typename... Strings>
void AppendToString(std::string *concat_str, const String &s, Strings... strs)
{
    concat_str->append(s);
    AppendToString(concat_str, strs...); // 합쳐진 문자열을 계속 다음 함수로 보낸다.
}

template <typename String, typename... Strings>
std::string StrCat(const String &s, Strings... strs)
{
    // 먼저 합쳐질 문자열의 총 길이를 구한다.
    size_t total_size = GetStringSize(s, strs...);

    // reserve 를 통해 미리 공간을 할당해 놓는다.
    std::string concat_str;
    concat_str.reserve(total_size);

    concat_str = s;
    AppendToString(&concat_str, strs...);

    return concat_str;
}

template <typename T>
int func1(T num)
{
    std::cout << num;
    return 0;
}
template <typename T, typename... Ts>
int func1(T num, Ts... nums)
{
    std::cout << num;
    func1(nums...);
    return 0;
}

int sum_all() { return 0; } // 베이스케이스.
template <typename... Ints>
int sum_all(int num, Ints... nums)
{
    return num + sum_all(nums...);
}

///////////////////
template <typename... Ints>
double average(Ints... nums){
    std::cout << sizeof...(nums);
    return static_cast<double>(sum_all(nums...)) / sizeof...(nums);
}

template <typename... Ints>
int sum_all(Ints... nums) {
  return (... + nums);
}
////////////////////
class A {
 public:
  void do_something(int x) const {
    std::cout << "Do something with " << x << std::endl;
  }
};

template <typename T, typename... Ints>
void do_many_things(const T& t, Ints... nums) {
  // 각각의 인자들에 대해 do_something 함수들을 호출한다.
  (t.do_something(nums), ...);
}
int main() {
  A a;
  do_many_things(a, 1, 3, 2, 4);
}

int main()
{
    // std::string 과 const char* 을 혼합해서 사용 가능하다.
    std::cout << StrCat(std::string("this"), " ", "is", " ", std::string("a"),
                        " ", std::string("sentence"));
    func1(1, 2, 3, 4, 5);

    std::cout <<average(); //nan 이 출력된다    
    //std::cout << 5/0; //이건 안되는데
    double x=5;
    double y=0;
    double z=0;
    double i = 5;
    std::cout <<x/y; //inf 출력
    //std::cout <<x/0;
    std::cout <<z/y; //nan 출력
    //std::cout <<i/0;

    //결론
    /*
    0을 0으로 나눈 경우 -> nan
    임의의 부동소숫점 수를 0으로 나눈 경우 -> inf or -inf 이다

    정수로 연산될 경우에는
    division zero로 런타임 에러를 발생시킨다.

    중요한것은 나누는 0의 자료형으로
    0이 부동소숫점이면 inf or nan
    0이 정수이면 런타임 에러를 발생시키는 것으로 보인다.
    
    */

   std::cout << sum_all(1, 4, 2, 3, 10) << std::endl;
   A a;
   do_many_things(a,1,2,3,4);
}
