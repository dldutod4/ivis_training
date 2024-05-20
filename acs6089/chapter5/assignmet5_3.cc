#include <iostream>
class Array;
class Operand;

class Array
{
private:
    friend Operand;

    //
    int dimension;

    //
    int* dimension_size;

    //
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

    for (size_t i = 0; i < dimension_size[0]; i++)
    {
        std::cout << "**arr[" << i << "]" << std::endl;
        for (size_t j = 0; j < dimension_size[1]; j++)
        {
            std::cout << "*array[" << i << "][" << j << "] : ";
            for (size_t k = 0; k < dimension_size[2]; k++)
            {
            std::cout << elements[dimension_size[1]*(dimension_size[2]*i+j)+k] << " ";
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
    if(level != array->dimension)
        location = array->dimension_size[array->dimension - level] * (idx + location);
    else
        location += idx;
    std::cout << location << std::endl;
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
    array->elements[location] = a;
}

int main()
{
    int dim = 3;
    int dim_s[3] = {2, 3, 4};
    int a = 1;

    Array arr(dim, dim_s);

    
    for (size_t i = 0; i < dim_s[0]; i++)
    {
        for (size_t j = 0; j < dim_s[1]; j++)
        {
            for (size_t k = 0; k < dim_s[2]; k++)
            {
                arr[i][j][k] = a++;
            }
        }
    }
    

    arr[1][2][3] = 3;
    arr.dim_3_arr_show();
    return 0;
}