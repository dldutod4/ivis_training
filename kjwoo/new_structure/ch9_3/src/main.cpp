/* 나만의 std::array 구현 */
#include <iostream>

template <typename T, unsigned int N>  // 타입이 아닌 인수 전달.
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

///////////////////////////////////
// 비율계산

template <int X, int Y>
struct GCD {
    static const int value = GCD<Y, X % Y>::value;
};

template <int X>
struct GCD<X, 0> {
    static const int value = X;
};

template <int N, int D = 1>
struct Ratio {
    typedef Ratio<N, D> type;
    static const int num = N;  // 분자
    static const int den = D;  // 분모
};
template <class R1, class R2>
struct _Ratio_add {  // 분수간 덧셈
    typedef Ratio<R1::num * R2::den + R2::num * R1::den, R1::den * R2::den> type;
};

template <class R1, class R2>
struct Ratio_add : _Ratio_add<R1, R2>::type {};
// Ratio_add는 _Ratio_add의 type을 상속받기 때문에
//_Ratio_add::type::num 을 Ratio_add::num으로 사용이 가능하다.

int main() {
    typedef Ratio<2, 3> rat;
    typedef Ratio<3, 2> rat2;
    typedef Ratio_add<rat, rat2> rat3;

    std::cout << rat3::num << " / " << rat3::den << std::endl;

    return 0;
}
