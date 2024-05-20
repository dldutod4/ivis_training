// 문제 2

//     get_number 함수를 cstdlib 의 atof 함수를 이용해서 좀 더 간단하게 나타내보세요.

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
    num = atof(str+from); //atof 함수사용해 처리.
    std::cout << num << std::endl;
    if(minus) num*=-1.0;

    return num;
}