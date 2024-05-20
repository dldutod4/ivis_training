//  문제 1

// N 차원 배열을 제공하는 클래스를 만들어보세요.
// 이는 여러분이 여태까지 배운 내용을 시험할 것입니다.
// 참고로, 원소에 접근하기 위해서는 a[1][2][3] 과 같은 방법으로 접근하겠지요.
// 다만 N 차원 배열이기 때문에 (N은 객체 생성시에 사용자가 입력합니다)
// 2 차원 배열은 a[1][2], 3 차원 배열은 a[1][2][3] 과 같은 방식으로 접근할 것입니다. (난이도 : 最上)
/*

//선언 방법
Num a(3)
3차일 때
a[3][0][2] 는 몇번째 데이터인가?
배열의 구조를 알 수 없으므로 몇번째인지 지정이 안된다

방법 1
배열의 구조를 10x10x10...으로 고정

*방법 2*
선언 시 배열의 구조를 입력
배열의 구조를 1차원 배열로 입력받아 저장할 수 있다.

구조를 저장할때
현 차수의 이전차수들의 길이들의 곱을 저장해뒀다가
현 차수의 인덱스 * 이전차수들 길이 곱으로 [] 연산시에 총 인덱스에 더하여 사용

ex)
a[3][4][6]의 구조를 가진 배열일때
structure = {1*6*4, 1*6, 1} 로 구조를 저장하고
a[1][2][3]에 저장된 자료를 꺼낼때
((a[].(3)).[](2)).[](1) 로 실행 되므로

1. a[].(3)
x += structure[0] * 3
2. a[].(2)
x += structure[1] * 2
3. a[].(1)
x += structure[2] * 1

을 거쳐 최종 인덱스가 결정되어 x가 저장되고

호출 혹은 대입연산시
data.[x]를 사용하고 x를 0으로 초기화한다.

*/
#include <iostream>

class Num
{
    int *data;      // 입력한 모든 데이터
    int n;          // n차
    int *structure; // 구조 ->이전차수들 길이의 곱을 저장
    int k;          // 연쇄호출횟수
    int x;          // 인덱스 지정

public:
    Num(const int inpN, const int *inpStructure);
    Num(const Num &cp);
    ~Num();
    Num &operator[](int subScript);

    friend std::ostream &operator<<(std::ostream &os, Num &num);
    Num &operator=(int inp);
    Num &operator=(Num &num);
};
Num::~Num(){
    delete[] data;
    delete[] structure;
}
Num::Num(const int inpN, const int *inpStructure)
{
    n = inpN;
    int len = 1;
    for (int i = 0; i < n; i++) // 길이 계산
    {
        len *= inpStructure[i];
        
    }
    if(len <= 0){
        std::cout <<"구조는 0 이상의 배열로 입력해야합니다."<<std::endl;
        return;
    }
    data = new int[len];
    structure = new int[n];

    // 구조 저장
    structure[n-1] = 1;
    for (int i = n-2; i >= 0; i--) 
    {
        structure[i] = structure[i+1] * inpStructure[i+1]; //이전차수들 길이의 곱을 저장해둔다.
        //ex [4][5][6] -> structure :{30,6,1}
    }
    k = 0;
    x = 0;
    std::cout << "선언배열 길이:" << len << std::endl;
}
Num::Num(const Num &cp)
{
    n = cp.n;
    int len = 1;
    for (int i = 0; i < n; i++)
    {
        len *= cp.structure[i];
    }
    data = new int[len];
    for (int i = 0; i < len; i++) // 데이터 복사
    {
        data[i] = cp.data[i];
    }
    structure = new int[n];
    for (int i = 0; i < n; i++) // 구조 복사
    {
        structure[i] = cp.structure[i];
        
    }
    k = 0;
    x = 0;
    std::cout << "선언배열 길이:" << len << std::endl;
}
Num &Num::operator[](int subScript)
{
    x += structure[k++] * subScript; //k 차수 이전 차수들의 길이 곱 * 현 인덱스
    if (n == k) {
        k = 0;
        //std::cout <<"x:"<< x << std::endl;
    }
    return *this;
}
std::ostream &operator<<(std::ostream &os, Num &num)
{
    if(num.k > 0){
        num.k=0;
    }
    os << num.data[num.x];
    num.x = 0;
    return os;
}
Num &Num::operator=(int inp)
{
    if(k > 0){
        k=0;
    }
    data[x] = inp;
    x = 0;
    return *this;
}
Num &Num::operator=(Num &num)
{
    if(k > 0){
        k=0;
    }
    data[x] = num.data[num.x];
    x = 0;
    num.x = 0;
    return *this;
}
int main()
{
    int x[3] = {4, 3, 2};
    int y[2] = {2, 2};
    Num a(3, x);
    Num b(2, y);
    int arr[3][4][2];

    std:: cout << &arr[3][4] <<std::endl; 
    std:: cout << &arr[3][4][0] <<std::endl;
    a[3][2][1] = 3;
    
    a[3][0][0] = 8;
    b[1][1] = 6;
    b[0][0] = a[3][0][0];

    std::cout << a[3][2][1] << std::endl;
    std::cout << a[3][0][0] << std::endl;
    std::cout << a[3][0]<<std::endl; // []를 차수만큼 호출안해도 사용가능
    std::cout << a[3]<<std::endl;   // 위와 동일

    std::cout << b[1][1] << std::endl;
    std::cout << b[0][0] << std::endl;

}