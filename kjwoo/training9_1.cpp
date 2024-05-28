// 템플릿
// 데이터 타입이 바뀔때마다 타입을 바꿔 다시 만들기 힘들다.

/*

템플릿 사용법 
template <typename T> 이하에 선언되는 클래스에 대해 템플릿을 정의하고 인자로 T를 받는다는 것을 의미

템플릿으로 클래스를 생성했을때 해당 클래스는 자신이 어떤 타입을 인자로 받았는지 저장하게된다.
외부에서 어떤 타입을 인자로 받았는 지 필요할 때가 있기 때문이다
따라서 템플릿으로 형성되는 클래스에는 
typedef T value_type; 를 추가한다.

//특정타입에 대해서만 따로 정의도 가능하다
template<>
class vector<bool> 이면 bool일때만 따로 정의된다.

여러 타입을 인자로 넘길수도 있다.
template <typename A, typename B, typename C>
template <

*/
//  템플릿 첫 활용
#include <iostream>
#include <string>

template <typename T> //아래 Vector클래스에 대한 템플릿을 명시
class Vector
{
    T *data;
    int capacity;
    int length;

public:
    // 생성자
    Vector(int n = 1) : data(new T[n]), capacity(n), length(0) {}

    // 맨 뒤에 새로운 원소를 추가한다.
    void push_back(T s)
    {
        if (capacity <= length)
        {
            T *temp = new T[capacity * 2];
            for (int i = 0; i < length; i++)
            {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
            capacity *= 2;
        }

        data[length] = s;
        length++;
    }

    // 임의의 위치의 원소에 접근한다.
    T operator[](int i) { return data[i]; }

    // x 번째 위치한 원소를 제거한다.
    void remove(int x)
    {
        for (int i = x + 1; i < length; i++)
        {
            data[i - 1] = data[i];
        }
        length--;
    }

    // 현재 벡터의 크기를 구한다.
    int size() { return length; }

    ~Vector()
    {
        if (data)
        {
            delete[] data;
        }
    }
};

int main()
{
    // int 를 보관하는 벡터를 만든다.
    Vector<int> int_vec;
    int_vec.push_back(3);
    int_vec.push_back(2);

    std::cout << "-------- int vector ----------" << std::endl;
    std::cout << "첫번째 원소 : " << int_vec[0] << std::endl;
    std::cout << "두번째 원소 : " << int_vec[1] << std::endl;

    Vector<std::string> str_vec;
    str_vec.push_back("hello");
    str_vec.push_back("world");
    std::cout << "-------- std::string vector -------" << std::endl;
    std::cout << "첫번째 원소 : " << str_vec[0] << std::endl;
    std::cout << "두번째 원소 : " << str_vec[1] << std::endl;
}