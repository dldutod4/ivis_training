#include <iostream>

//T는 행렬의 자료형을 받고 N은 행렬의 크기를 받는다
template <typename T, unsigned int N>
class Array {
  T data[N];

 public:
  // 배열을 받는 레퍼런스 arr
  Array(T (&arr)[N]) {
    for (int i = 0; i < N; i++) {
      data[i] = arr[i];
    }
  }

  T* get_array() { return data; }

  unsigned int size() { return N; }

  void print_all() {
    for (int i = 0; i < N; i++) {
      std::cout << data[i] << ", ";
    }
    std::cout << std::endl;
  }
};

int main() {
  int arr[3] = {1, 2, 3};

  // 배열 wrapper 클래스
  //T자리에는 int형이 N 자리에는 3이 들어가 int형 1차원 3크기의 행렬 생성
  Array<int, 3> arr_w(arr);

  arr_w.print_all();

  //Array<int, 3> 와 Array<int, 5>는 N이 서로 다른 인자로 인스턴스화 되었기 때문에 다른 클래스가 된다.
  std::cout << (typeid(Array<int, 3>) == typeid(Array<int, 5>)) << std::endl;
}