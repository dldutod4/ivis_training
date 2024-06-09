//아래의 Vector 클래스도 2차원 이상의 vector를 생성하라

#include <iostream>

template <typename T>
class Vector
{
    T* data;
    int size;

public:
    Vector();
    ~Vector();
};