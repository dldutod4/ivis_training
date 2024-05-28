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

struct User {
    std::string name;
    int age;

    User(std::string name, int age) : name(name), age(age) {}

    bool operator<(const User& u) const { return age < u.age; }
};
std::ostream& operator<<(std::ostream& o, const User& u) {
    o << u.name << " , " << u.age;
    return o;
}

int stable_main() {
    std::vector<User> vec;
    for (int i = 0; i < 100; i++) {
        std::string name = "";
        name.push_back('a' + i / 26);
        name.push_back('a' + i % 26);
        vec.push_back(User(name, static_cast<int>(rand() % 10)));
    }

    std::vector<User> vec2 = vec;

    std::cout << "정렬 전 ----" << std::endl;
    print(vec.begin(), vec.end());

    std::sort(vec.begin(), vec.end());

    std::cout << "정렬 후 ----" << std::endl;
    print(vec.begin(), vec.end());

    std::cout << "stable_sort 의 경우 ---" << std::endl;  // 원소가 들어간 순서가 보존된다.
    std::stable_sort(vec2.begin(), vec2.end());
    print(vec2.begin(), vec2.end());
    return 0;
}
int sort_main() {
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
    std::sort(vec.begin(), vec.end());  // RandomAccessIterator만 사용가능

    std::cout << "정렬 후 ----" << std::endl;
    print(vec.begin(), vec.end());
    return 0;
}
int sort2_main() {
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
    // std::sort(vec.begin(), vec.end(), int_compare());  // 함수객체를 전달해 내림차순정렬.
    std::sort(vec.begin(), vec.end(), std::greater<int>());

    std::cout << "정렬 후 ----" << std::endl;
    print(vec.begin(), vec.end());
    return 0;
}

#include <functional>

struct is_odd {
    bool operator()(const int& i) { return i % 2 == 1; }
};
int removeif_main() {
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    std::cout << "처음 vec 상태 ------" << std::endl;
    print(vec.begin(), vec.end());

    std::cout << "벡터에서 홀수 인 원소 제거 ---" << std::endl;
    // 함수객체 odd를 전달해 특정조건을 전달한다.
    vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd()), vec.end());
    print(vec.begin(), vec.end());
    return 0;
}
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

struct is_odd2 {
    int num_delete;

    is_odd2() : num_delete(0) {}

    bool operator()(const int& i) {
        if (num_delete >= 2) return false;

        if (i % 2 == 1) {
            num_delete++;
            return true;
        }

        return false;
    }
};
int removeif2_main() {
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    std::cout << "처음 vec 상태 ------" << std::endl;
    print(vec.begin(), vec.end());

    std::cout << "벡터에서 홀수인 원소 앞의 2개 제거 ---" << std::endl;
    vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd2()), vec.end());
    print(vec.begin(), vec.end());
    return 0;
}
struct is_odd3 {
    int* num_delete;

    is_odd3(int* num_delete) : num_delete(num_delete) {}

    bool operator()(const int& i) {
        if (*num_delete >= 2) return false;

        if (i % 2 == 1) {
            (*num_delete)++;
            return true;
        }

        return false;
    }
};
int removeif3_main() {
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    std::cout << "처음 vec 상태 ------" << std::endl;
    print(vec.begin(), vec.end());

    std::cout << "벡터에서 홀수인 원소 앞의 2개 제거 ---" << std::endl;
    int num_delete = 0;
    vec.erase(std::remove_if(vec.begin(), vec.end(), is_odd3(&num_delete)), vec.end());
    // 함수객체를 외부변수 num_delete의 포인터까지 생성자에 넣어 함께 생성해 사용.
    print(vec.begin(), vec.end());
    return 0;
}

int lambda_main() {
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    std::cout << "처음 vec 상태 ------" << std::endl;
    print(vec.begin(), vec.end());

    std::cout << "벡터에서 홀수인 원소 제거 ---" << std::endl;
    vec.erase(std::remove_if(vec.begin(), vec.end(), [](int i) -> bool { return i % 2 == 1; }), vec.end());
    print(vec.begin(), vec.end());
    return 0;
}
int transform_main() {
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(3);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    std::cout << "처음 vec 상태 ------" << std::endl;
    print(vec.begin(), vec.end());

    std::cout << "벡터 전체에 1 을 더한다" << std::endl;
    std::transform(vec.begin(), vec.end(), vec.begin(), [](int i) { return i + 1; });
    print(vec.begin(), vec.end());
    return 0;
}

int main() {
    // sort_main();
    // sort2_main();
    // stable_main();
    // removeif_main();
    // removeif2_main();
    // removeif3_main();
    // lambda_main();
    transform_main();
}