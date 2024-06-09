// 대망의 Array 배열
#include <iostream>

namespace MyArray {
class Array;

//Array 클래스 내부에서 Int 클래스를 사용 및 인식하기 위해서 먼저 맨 위에서 미리 선언해 두어야한다.
class Int;

class Array {
  friend Int;

  const int dim;  // 몇 차원 배열 인지
  int* size;  // size[0] * size[1] * ... * size[dim - 1] 짜리 배열이다.

  struct Address {
    int level;
    // 맨 마지막 레벨(dim - 1 레벨) 은 데이터 배열을 가리키고, 그 위 상위
    // 레벨에서는 다음 Address 배열을 가리킨다.
    void* next;
  };

  Address* top;

 public:
  
  class Iterator
  {
    //현재 Iterator가 어떤 원소를 가리키고 있는지에 대한 정보를 맴버 변수로 가지고 있어야한다.
    //location에는 현재 Iterator가 가르키는 위치를 N 차원 배열에서 N개의 원소를 가지고 있는 1차원 배열로 저장한다.
    //ex) arr[1][2][3]의 원소를 가르킬 때 location = {1, 2, 3}
    int* location;
    Array* arr;

    friend Int;

   public:
    Iterator(Array* arr, int* loc = NULL) : arr(arr)
    {
      //N차원 배열에서 N개의 원소를 갖는 location 1차원 배열 생성
      location = new int[arr->dim];

      //실제 정보를 갖고 있는 int형 배열을 만나면 해당 차원의 깊이를 알 수 있고 그 값을 아니면 0을 location[i]에 저장한다
      for (int i = 0; i != arr->dim; i++)
        location[i] = (loc != NULL ? loc[i] : 0);
    }

    Iterator(const Iterator& itr) : arr(itr.arr)
    {
      location = new int[arr->dim];
      for (int i = 0; i != arr->dim; i++) location[i] = itr.location[i];
    }
    ~Iterator() { delete[] location; }

    // 다음 원소를 가리키게 된다.
    Iterator& operator++() {
      if (location[0] >= arr->size[0]) return (*this);

      bool carry = false;  // 받아 올림이 있는지
      int i = arr->dim - 1; // location에 저장된 원소의 위치가 arr 차원보다 한개 더 낮기 때문에 불러온 dim에 1을 뺀다
      do {
        // 어차피 다시 돌아온다는 것은 carry 가 true
        // 라는 의미 이므로 ++ 을 해야 한다.
        location[i]++;

        //Iterator가 위치하고 있는 부분이 각 차원의 크기보다 클 경우 carry가 발생한다.
        if (location[i] >= arr->size[i] && i >= 1)
        {
          // i 가 0 일 경우 0 으로 만들지 않는다 (이러면 begin 과 중복됨)
          location[i] -= arr->size[i];
          carry = true;
          i--;
        } else
          carry = false;

      } while (i >= 0 && carry);

      return (*this);
    }
    Iterator& operator=(const Iterator& itr) {
      arr = itr.arr;
      location = new int[itr.arr->dim];
      for (int i = 0; i != arr->dim; i++) location[i] = itr.location[i];

      return (*this);
    }
    Iterator operator++(int) {
      Iterator itr(*this);
      ++(*this);
      return itr;
    }
    bool operator!=(const Iterator& itr) {
      if (itr.arr->dim != arr->dim) return true;

      for (int i = 0; i != arr->dim; i++) {
        if (itr.location[i] != location[i]) return true;
      }

      return false;
    }
    Int operator*();
  };



  friend Iterator;
  Array(int dim, int* array_size) : dim(dim) {
    size = new int[dim];

    //size 배열에 각 차원에 대한 정보를 저장 
    // ex) arr[4][2][1] -> size[0] = 4, size[1] = 2, size[2] = 1
    for (int i = 0; i < dim; i++) size[i] = array_size[i];

    top = new Address;
    top->level = 0;

    initialize_address(top);
  }
  Array(const Array& arr) : dim(arr.dim) {
    size = new int[dim];
    for (int i = 0; i < dim; i++) size[i] = arr.size[i];

    top = new Address;
    top->level = 0;

    initialize_address(top);
    // 내용물 복사
    copy_address(top, arr.top);
  }

  //복사 생성자를 사용할 때 꼭 내부에 있는 모든 원소들을 복사해주어야한다.
  void copy_address(Address* dst, Address* src)
  { 
    if (dst->level == dim - 1) {
      for (int i = 0; i < size[dst->level]; ++i)
        static_cast<int*>(dst->next)[i] = static_cast<int*>(src->next)[i];
      return;
    }
    for (int i = 0; i != size[dst->level]; i++) {
      Address* new_dst = static_cast<Address*>(dst->next) + i;
      Address* new_src = static_cast<Address*>(src->next) + i;
      copy_address(new_dst, new_src);
    }
  }

  // address 를 초기화 하는 함수이다. 재귀 호출로 구성되어 있다.
  void initialize_address(Address* current)
  {
    //입력 받은 current(Address*) 가 NULL 이면 종료
    if (!current) return;

    //dim-1 레벨에는 실제 정보가 저장되는 배열의 주소가 저장되어야하므로 재귀함수를 호출하지 않는다.
    if (current->level == dim - 1)
    {
      //맨 마지막 레벨인 dim-1에는 실제 값이 저장되는 int 배열의 시작 주소가 들어간다.
      current->next = new int[size[current->level]];
      return;
    }

    //각 level(또는 차원)에 필요한 크기를 저장하고 있는 size 배열을 통해 필요한 Address 배열 갯수에 맞게 할당 
    current->next = new Address[size[current->level]];

    //할당된 Address 배열 내부에 다음(next) level에 해당하는 부분을 수행하기 위해 반복
    for (int i = 0; i != size[current->level]; i++)
    {
      //현재 level에 해당하는 할당 작업이 끝났으므로 다음(next) level을 수행할 수 있도록 level 증가
      (static_cast<Address*>(current->next) + i)->level = current->level + 1;

      //다음(next) level 초기화를 재귀 함수로 시행
      initialize_address(static_cast<Address*>(current->next) + i);
    }
  }

  void delete_address(Address* current)
  {
    //입력 받은 current(Address*) 가 NULL 이면 종료
    if (!current) return;

    for (int i = 0; current->level < dim - 1 && i < size[current->level]; i++)
    {
      delete_address(static_cast<Address*>(current->next) + i);
    }

    if (current->level == dim - 1) {
      delete[] static_cast<int*>(current->next);
    }
    delete[] static_cast<Address*>(current->next);
  }
  Int operator[](const int index);
  ~Array() {
    delete_address(top);
    delete[] size;//size 역시 동적으로 할당 되었기 때문에 꼭 delete 하여야 한다.
  }

  //iterator의 시작과 끝을 알아야 맨 마지막 끝을 벋어나는 부분까지 진행되게 하지않는다.
  //iterator의 시작 부분은 arr[1][2][3]일 때 location = {0,0,0}으로 시작한다.
  Iterator begin() {
    int* arr = new int[dim];
    for (int i = 0; i != dim; i++) arr[i] = 0;

    Iterator temp(this, arr);
    delete[] arr;

    return temp;
  }

  //iterator의 끝 부분은 arr[1][2][3]일 때 arr[1][2][3]에서 하나 더 진행한 부분인 location = {2, 0, 0}으로 지정
  Iterator end() {
    int* arr = new int[dim];
    arr[0] = size[0];
    for (int i = 1; i < dim; i++) arr[i] = 0;

    Iterator temp(this, arr);
    delete[] arr;

    return temp;
  }
};


class Int {
  //data는 다음 레벨의 Address 주소 또는 int 배열의 시작 주소를 가지고 있다.
  void* data;

  //Int 클래스가 실제 정보를 가지고 있는 마지막 level의 객체인지 아니면 중간 단계의 객체인지 구별하기 위해 필요
  int level;
  Array* array;

 public:
 //default argument를 사용해 주므로써 인자들에 정보가 주워지지 않더라도 자동으로 해당 인자들을 넣어서 생성한다
 //defualt argument를 사용할 때 연속적으로만 사용할 수 있으므로 중간을 건너뛰고 사용하면 경고를 발생하지 않기에 오류를 발생할 수 있다.
  Int(int index, int _level = 0, void* _data = NULL, Array* _array = NULL)
      : level(_level), data(_data), array(_array)
  {
    //level이 1보다 작은 값이 입력되거나 미리 입력된 각 차원의 범위를 벋어나는 값이 index로 들어오면 시행하지 않는다
    if (_level < 1 || index >= array->size[_level - 1])
    {
      data = NULL;
      return;
    }

    //맨 마지막 level인 실제 자료가 저장되는 int형 배열의 시작 주소에 접근할 경우
    if (level == array->dim)
    {
      // 이제 data 에 int 자료형을 저장한다.
      data = static_cast<void*>((
          static_cast<int*>(static_cast<Array::Address*>(data)->next) + index));
    }
    else
    {
      // 그렇지 않을 경우 data 에 그냥 다음 addr 을 넣어준다.
      data = static_cast<void*>(static_cast<Array::Address*>(
                                static_cast<Array::Address*>(data)->next) +
                                index);
    }
  };

  Int(const Int& i) : data(i.data), level(i.level), array(i.array) {}

  //void* 형으로 받아온 data를 Int 객체의 data의 형태인 int형 1차원 배열로 바꿔주는 operator
  operator int()
  {
    if (data) return *static_cast<int*>(data);
    return 0;
  }

  Int& operator=(const int& a) {
    if (data) *static_cast<int*>(data) = a;
    return *this;
  }

  Int operator[](const int index) {
    if (!data) return 0;
    return Int(index, level + 1, data, array);
  }
};

//구체적인 Int 클래스 내부의 정보(생성자)를 사용하는 경우에는 반드시 Int 클래스의 정의가 선행되어야함
//따라서 Array클래스의 operator[]는 Int 내부의 data, level 등을 사요하기 때문에 맨 마지막에 따로 작성되어야함
Int Array::operator[](const int index) {
  return Int(index, 1, static_cast<void*>(top), this);
}

Int Array::Iterator::operator*() {
  Int start = arr->operator[](location[0]);
  for (int i = 1; i <= arr->dim - 1; i++) {
    start = start.operator[](location[i]);
  }
  return start;
}
}  // namespace MyArray

int main() {
  int size[] = {2, 3, 4};
  MyArray::Array arr(3, size);

  MyArray::Array::Iterator itr = arr.begin();
  for (int i = 0; itr != arr.end(); itr++, i++) (*itr) = i;
  for (itr = arr.begin(); itr != arr.end(); itr++)
    std::cout << *itr << std::endl;

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 4; k++) {
        arr[i][j][k] = (i + 1) * (j + 1) * (k + 1);
      }
    }
  }
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 4; k++) {
        std::cout << i << " " << j << " " << k << " " << arr[i][j][k]
                  << std::endl;
      }
    }
  }
}