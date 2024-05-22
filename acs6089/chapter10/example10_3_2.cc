#include <algorithm>
#include <iostream>
#include <vector>

template <typename Iter>
void print(Iter begin, Iter end) {
  while (begin != end) {
    std::cout << *begin << " ";
    begin++;
  }
  std::cout << std::endl;
}
struct int_compare {
  bool operator()(const int& a, const int& b) const { return a > b; }
};
int main() {
  std::vector<int> vec;
  vec.push_back(5);
  vec.push_back(3);
  vec.push_back(1);
  vec.push_back(6);
  vec.push_back(4);
  vec.push_back(7);
  vec.push_back(2);

  std::cout << "정렬 전 ----" << std::endl;
  print(vec.begin(), vec.end());

  //vec.begin()부터 vec.end()까지의 원소 중 vec.begin()에서 vec.begin() + 3에
  //전체에서 추가 조건인 가장 큰 순서대로 저장하고 나머지는 그대로 둔다.
  std::partial_sort(vec.begin(), vec.begin() + 3, vec.end(), int_compare());

  std::cout << "정렬 후 ----" << std::endl;
  print(vec.begin(), vec.end());
}