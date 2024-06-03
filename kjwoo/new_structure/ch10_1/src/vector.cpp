#include "vector.h"
using itr = std::vector<int>::iterator;

template <typename T>
void print_vector(std::vector<T>& vec) {
    // 전체 벡터를 출력하기
    std::cout << "[ ";
    for (typename std::vector<T>::iterator itr = vec.begin(); itr != vec.end(); ++itr) {
        std::cout << *itr << " ";
    }
    std::cout << "]";
}
template <typename T>
void print_vector_range_based(std::vector<T>& vec) {
    // 전체 벡터를 출력하기
    for (const auto& elem : vec) {
        std::cout << elem << std::endl;
    }
}
int vector_main() {
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);
    vec.push_back(20);

    std::cout << "처음 벡터 상태" << std::endl;
    print_vector(vec);

    std::vector<int>::iterator itr = vec.begin();
    std::vector<int>::iterator end_itr = vec.end();

    for (; itr != end_itr; ++itr) {
        if (*itr == 20) {
            vec.erase(itr);
        }
    }

    std::cout << "값이 20 인 원소를 지운다!" << std::endl;
    print_vector(vec);

    /*
      원래 10 20 30 40 20 이었던 배열에서 저렇게 지우면
      10 30 40 이 남아야할 것같은데
      10 30이 출력되는것이 이상함.

      erase나 insert를 하면 반복자가 무효화 되는 것은 알지만
      컴파일 에러가 아닌 [10 30]을 출력하는 것이 이상하다.

    */
    return 0;
}