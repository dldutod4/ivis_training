
#include<iostream>
#include<string.h>
#include<cstdlib>
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
        if(img >0){
            std::cout << real << "+" << img << "i" << std::endl;
        }
        else if(img < 0){
            std::cout << real  << img << "i" << std::endl;
        }
        else{
            std::cout << real <<std::endl;
        }
        
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
    num = atof(str+from);
    std::cout << num << std::endl;
    if(minus) num*=-1.0;

    return num;
}
// }
// double Complex::get_number(const char *str, int from, int to) const
// {
//     bool minus = false;
//     if (from > to)
//         return 0;
//     if (str[from] == '-')
//         minus = true;
//     if (str[from] == '-' || str[from] == '+')
//         from++; // 부호 붙였을때 다음자리부터 읽음.

//     double num = 0.0;
//     double decimal = 1.0;
//     bool integer_part = true;
//     for (int i = from; i <= to; i++)
//     {
//         if (isdigit(str[i]) && integer_part)
//         {
//             num *= 10.0;
//             num += (str[i] - '0');
//         }
//         else if (str[i] == '.')
//             integer_part = false;
//         else if (isdigit(str[i]) && !integer_part)
//         {
//             decimal /= 10.0;
//             num += ((str[i] - '0') * decimal);
//         }
//         else
//             break;
//     }
//     if (minus) num *= -1.0;

//     return num;
// }
int main()
{
    Complex num("10-i20");
    num.show();

}