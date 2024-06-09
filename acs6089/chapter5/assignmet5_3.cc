#include <iostream>
class Array;
class Operand;

class Array
{
private:
    friend Operand;

    //행렬의 차원을 저장
    int dimension;

    //각 차원의 크기를 저장
    int* dimension_size;

    //모든 원소를 1차원 행렬에 저장
    int* elements;

public:
    Array(int dim, int* dim_s);
    ~Array();

    //3차원 행렬 표현하는 함수
    void dim_3_arr_show();

    //[]연산자를 만나면 array가 취하는 행동
    Operand operator[](const int index);
};

Array::Array(int dim, int* dim_s) : dimension(dim), dimension_size(dim_s)
{
    int total_size = 1;
    for (size_t i = 0; i < dim; i++)
    {
        total_size *= dim_s[i];
    }
    std::cout << total_size << " size array created" << std::endl;
    elements = new int[total_size];
}

Array::~Array()
{
    delete[] elements;
}

void Array::dim_3_arr_show()
{
    if(dimension != 3)
    {
        std::cout << "this array is not 3 dimension array" << std::endl;
        return;
    }

    int a = 0;
    for (size_t i = 0; i < dimension_size[0]; i++)
    {
        std::cout << "**arr[" << i << "]" << std::endl;
        for (size_t j = 0; j < dimension_size[1]; j++)
        {
            std::cout << "*array[" << i << "][" << j << "] : ";
            for (size_t k = 0; k < dimension_size[2]; k++)
            {
                std::cout << elements[a] << " ";
                a++;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

class Operand
{
private:
    Array* array;
    int location;
    int level;
public:
    Operand(Array* arr, int lev, int loc, int idx);
    ~Operand();

    Operand operator[](const int idx);

    void operator=(const int& value);
};

Operand::Operand(Array* arr, int lev, int loc, int idx) : array(arr), level(lev), location(loc)
{
    //행렬의 마지막 차원에 도달하면 더 이상 곱할 변수가 없이 idx를 바로 더하면된다.
    if(level == array->dimension)
        location += idx;

    //차원이 증가할때마다 각 차원의 다음 차원의 크기 만큼 곱해서 더해야 한다.
    else
        location = ((idx + location) * array->dimension_size[level]);
}

Operand::~Operand()
{
}

Operand Operand::operator[](const int idx)
{
    return Operand(this->array, this->level+1, this->location, idx);
}

Operand Array::operator[](const int idx)
{
    return Operand(this, 1, 0, idx);
}

void Operand::operator=(const int& a)
{
    int temp = array->elements[location];
    array->elements[location] = a;
    std::cout << "located at " << location << " changed " << temp << " to " << a << std::endl;
}

int main()
{
    int dim = 3;
    int dim_s[3] = {3, 5, 7};
    int a = 1;

    Array arr(dim, dim_s);
    arr.dim_3_arr_show();
    
    for (size_t i = 0; i < dim_s[0]; i++)
    {
        for (size_t j = 0; j < dim_s[1]; j++)
        {
            for (size_t k = 0; k < dim_s[2]; k++)
            {
                arr[i][j][k] = a;
                a++;
            }
        }
    }

    arr.dim_3_arr_show();
    return 0;
}