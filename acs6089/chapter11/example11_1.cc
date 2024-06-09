#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
 public:
  Vector(size_t size) : size_(size) {
    data_ = new T[size_];
    for (int i = 0; i < size_; i++) {
      data_[i] = 3;
    }
  }
  const T& at(size_t index) const {
    if (index >= size_) {
      throw std::out_of_range("vector 의 index 가 범위를 초과하였습니다.");
    }
    return data_[index];
  }
  ~Vector() { delete[] data_; }

 private:
  T* data_;
  size_t size_;
};
int main() {
  Vector<int> vec(3);

  int index, data = 0;
  std::cin >> index;

  try {
    data = vec.at(index);//해당 줄의 vec.at(index)의 내부 throw부분에서 exception 발생하고
    //바로 다음 부분으로 catch로 점프하여 catch문 안에 정의된 예외의 꼴에 맞는 객체를 받게 된다.
  } catch (std::out_of_range& e) {
    std::cout << "예외 발생 ! " << e.what() << std::endl;
  }
  // 예외가 발생하지 않았다면 3을 이 출력되고, 예외가 발생하였다면 원래 data 에
  // 들어가 있던 0 이 출력된다.
  std::cout << "읽은 데이터 : " << data << std::endl;
}