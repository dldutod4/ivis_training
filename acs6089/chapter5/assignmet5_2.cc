#include <iostream>
class Array;
class Operand;

class Array
{
  private:
  //arr[2][3][3]과 같이 여러개의 operator를 처리해야하면 기존의 Array의 반환형으로만은 어렵다 따라서 새로운 클래스가 필요
  friend Operand;

  //n차원의 n을 dimesion 정수형 변수에 저장한다.
  int dimension;

  //각 차원의 크기를 dimesion_size 정수형 배열에 저장한다.
  //ex) arr[4][5][6]이면 dimension_size[0] = 4, dimension_size[1] = 5, dimension_size[2] = 6으로 저장된다 
  int* dimension_size;

  struct Node
  {
    //현재 Node의 차원 level를 나타낸다.
    int level;

    //자신에게 종속된 노드들을 void 배열로 가지고 있는다.
    //void*인 이유는 n차원 배열에서 n-2 level까지는 종속 Node가 Node 구조체이나 마지막 n-1 level의 종속 Node는 실제 정보를 갖고 있는 int형 배열이기때문에 자유로운 형 변환을 위해 void*로 갖고 있는다.
    void* next_node;
  };
  
  Node* top;

  public:
  //Array 생성자
  Array(int dim, int* dim_s);
  
  //초기화 재귀 함수
  void initialize_nodes(Node* current);

  //각 원소에 접근하는 함수
  int* iterator(int* location);

  //실제 값인 원소를 바꾸는 함수
  void change_element(int* location, int value);

  //3차원 행렬 표현하는 함수
  void dim_3_arr_show();

  //[]연산자를 만나면 array가 취하는 행동
  Operand operator[](const int index);
};

//Array 생성자
Array::Array(int dim, int* dim_s) : dimension(dim)
{
  //dimension_size는 n차원 배열의 각 차원에 대한 크기를 가져야하므로 new을 통해 dim의 크기만큼의 int형 1차원 배열을 선언한다.
  dimension_size = new int[dim];

  //각 dimension_size를 입력받은 dim_s로 초기화 해준다.
  for (size_t i = 0; i < dim; i++)
  {
    dimension_size[i] = dim_s[i];
  }

  //가장 위쪽의 처음 노드를 할당하고 해당 노드의 깊이를 0으로 설정한다.
  top = new Node;
  top->level = 0;

  //선언한 배열을 재귀 함수로 초기화 및 할당한다.
  initialize_nodes(top);
};

//초기화 재귀함수
void Array::initialize_nodes(Node* current)
{
  //입력 받은 Node가 아무런 정보가 없는 깡통일때 초기화를 바로 종료
  if(current == NULL)return;

  //dimension-1 level의 종속 Node는 실제 int 값들을 저장하는 int형 1차원 배열이다.
  if(current->level == dimension -1)
  {
    current->next_node = new int[dimension_size[dimension -1]];

    //실제 값을 저장하는 int형 1차원 배열까지 모두 할당이 끝났으므로 더 이상 재귀함수를 호출하지 않고 끝낸다.
    return;
  }

  //각 Node는 종속 Node를 다음 level의 차원 크기에 해당하는 만큼 갖기때문에 아래와 같이 할당해준다.
  current->next_node = new Node[dimension_size[current->level]];

  //할당된 Node의 내부 정보들을 채워준다.
  for (size_t i = 0; i < dimension_size[current->level]; i++)
  {
    //종속된 Node 들의 level 정보를 입력한다.
    (static_cast<Node*>(current->next_node) + i)->level = current->level +1;

    //종속된 Node를 재귀 함수를 이용해 초기화 해준다.
    initialize_nodes(static_cast<Node*>(current->next_node) + i);
  }
};

//각 원소에 접근하는 함수
int* Array::iterator(int* location)
{
  //최상위 노드에서부터 목적지인 int형 배열에 접근하기 위해 시작 지점을 top Node로 설정
  Node* current = top;
  //top->level = 0;

  //실제 값이 저장된 level-1 전까지는 Node와 종속 Node로 연결되어 있기때문에 Node를 타고 찾아간다.
  for (size_t i = 0; i < dimension-1; i++)
  {
    current = (static_cast<Node*>(current->next_node) + location[i]);
  }

  //실제 값이 저장된 level에 접근하였으므로 해당 위치의 int형 포인터를 반환한다.
  return (static_cast<int*>(current->next_node) + location[dimension-1]);
}

//실제 값인 원소를 바꾸는 함수
void Array::change_element(int* location, int value)
{
  int* ptr = iterator(location);
  int temp;
  temp = *ptr;
  *ptr = value;

  //location에 위치한 원소가 원래 값에서 입력한 값으로 변경되었음을 알려주는 부분
  std::cout << "element which located {";
  for (size_t i = 0; i < dimension-1; i++)
  {
    std::cout << location[i] << ", ";
  }
  std::cout << location[dimension-1] <<"} changed " << temp << " to " << value << std::endl;
}

//3차원 행렬 표현함수
void Array::dim_3_arr_show()
{
  if(dimension != 3)
  {
    std::cout << "this array is not 3 dimension array" << std::endl;
    return;
  }

  int loc[3];
  for (size_t i = 0; i < dimension_size[0]; i++)
  {
    loc[0] = i;
    std::cout << "**arr[" << i << "]" << std::endl;
    for (size_t j = 0; j < dimension_size[1]; j++)
    {
      loc[1] = j;
      std::cout << "*array[" << i << "][" << j << "] : ";
      for (size_t k = 0; k < dimension_size[2]; k++)
      {
        loc[2] = k;
        std::cout << *iterator(loc) << " ";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
}

class Operand
{
  private:

  //현재 자신이 가르키고 있는 노드 또는 실제 값
  void* data;

  //현재 접근 중인 배열의 주소
  Array* array;

  //현재 진행 중인 level
  int level;

  public:
  //Operand의 기본 생성자
  Operand(void* data, Array* array, int level, int index);

  //[]연산자를 만나면 Operand가 취하는 행동
  Operand operator[](const int index);

  //=연산자를 만나면 Operand가 취하는 행동
  void operator=(const int& value);
};

Operand::Operand(void* data, Array* arr, int _level, int index) 
: array(arr) ,level(_level)
{
  //현재 접근 중인 배열에서 실제 데이터가 있는 위치까지 접근하였으므로 int*를 data에 저장한다.
  if(level == array->dimension)
  {
    Array::Node* temp = static_cast<Array::Node*>(data);
    int* target = static_cast<int*>(temp->next_node) + index + 1;
    std::cout << *target << std::endl;
    data = static_cast<void*>(target);
  }

  //아직 실제 값들이 저장되어 있는 level까지 접근하지 않았다.
  //따라서 중간 노드값을 다시 data에 저장해줘 마지막 level까지 접근할 수 있게 한다.
  else if(level < array->dimension)
  {
    std::cout << level << " " << index << std::endl;
    //void*형의 data를 Array 클래스의 Node* 형태로 사용하기 위해 temp에 변환하여 대입한다
    Array::Node* temp = static_cast<Array::Node*>(data);

    //[] 연산자를 이용해 받은 index에 해당하는 Node의 주소를 temp에 저장한다.
    temp = static_cast<Array::Node*>(temp->next_node) + index;

    //다음 Operand가 사용하기 위해 다시 void* 형으로 변환하여 data에 대입한다.
    data = static_cast<void*>(temp);
  }
}

Operand Operand::operator[](const int idx)
{
  //앞번째의 Operand에서 접근한 Node의 주소를 data를 통해 넘겨준다.
  return Operand(this->data, static_cast<Array*>(this->array), (this->level + 1), idx);
}

void Operand::operator=(const int& a)
{
  *static_cast<int*>(data) = a;
}

Operand Array::operator[](const int idx)
{
  //Array 클래스에서 넘어오며 현재 Array의 최상위 Node에서 부터 접근하기위해 top을 넘겨준다.
  //Array 클래스의 주소를 알려주어 현재 접근 중인 Array를 파악한다.
  //진행 중인 level을 넘겨 주어 실제 값이 저장되어 있는지 아닌지 파악한다.
  //접근할 i번째 Node를 idx로 알려준다.
  return Operand(static_cast<void*>(this->top), static_cast<Array*>(this), 1, idx);
}

int main()
{
  int dim = 3;
  int dim_s[3] = {2, 3, 4};
  int loc[3] = {1, 1, 1};
  int a = 1;

  Array arr(dim, dim_s);
  arr.dim_3_arr_show();

  arr.change_element(loc, 3);
  for (size_t i = 0; i < dim_s[0]; i++)
  {
    loc[0] = i;
    for (size_t j = 0; j < dim_s[1]; j++)
    {
      loc[1] = j;
      for (size_t k = 0; k < dim_s[2]; k++)
      {
        loc[2] = k;
        arr.change_element(loc, a++);
      }
    }
  }
  
  arr.dim_3_arr_show();
  arr[0][1][2] = 1;
  arr.dim_3_arr_show();
  return 0;
}