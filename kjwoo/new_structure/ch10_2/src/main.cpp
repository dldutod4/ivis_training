#include <iostream>
#include <map>
#include <set>
#include <string>
template <typename T>
void print_set(std::set<T>& s) {
    // 셋의 모든 원소들을 출력하기
    std::cout << "[ ";
    for (typename std::set<T>::iterator itr = s.begin(); itr != s.end(); ++itr) {
        std::cout << *itr << " ";
    }
    std::cout << " ] " << std::endl;
}
int set_main() {
    std::set<int> s;
    s.insert(10);
    s.insert(50);
    s.insert(20);
    s.insert(40);
    s.insert(30);

    std::cout << "순서대로 정렬되서 나온다" << std::endl;
    print_set(s);

    std::cout << "20 이 s 의 원소인가요? :: ";
    auto itr = s.find(20);
    if (itr != s.end()) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }

    std::cout << "25 가 s 의 원소인가요? :: ";
    itr = s.find(25);
    if (itr != s.end()) {
        std::cout << "Yes" << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }
    return 0;
}
///

template <typename T>
void print_set2(std::set<T>& s) {
    // 셋의 모든 원소들을 출력하기
    for (const auto& elem : s) {
        std::cout << elem << " " << std::endl;
    }
}
class Todo {
    int priority;
    std::string job_desc;

public:
    Todo(int priority, std::string job_desc) : priority(priority), job_desc(job_desc) {}

    bool operator<(const Todo& t) const {
        if (priority == t.priority) {
            return job_desc < t.job_desc;
        }
        return priority > t.priority;
    }

    friend std::ostream& operator<<(std::ostream& o, const Todo& td);
};

std::ostream& operator<<(std::ostream& o, const Todo& td) {
    o << "[ 중요도: " << td.priority << "] " << td.job_desc;
    return o;
}
int set2_main() {
    std::set<Todo> todos;

    todos.insert(Todo(1, "농구 하기"));
    todos.insert(Todo(2, "수학 숙제 하기"));
    todos.insert(Todo(1, "프로그래밍 프로젝트"));
    todos.insert(Todo(3, "친구 만나기"));
    todos.insert(Todo(2, "영화 보기"));

    print_set2(todos);

    std::cout << "-------------" << std::endl;
    std::cout << "숙제를 끝냈다면!" << std::endl;
    todos.erase(todos.find(Todo(2, "수학 숙제 하기")));
    print_set(todos);
    return 0;
}

template <typename K, typename V>
void print_map3(std::map<K, V>& m) {
    // 맵의 모든 원소들을 출력하기
    for (auto itr = m.begin(); itr != m.end(); ++itr) {
        std::cout << itr->first << " " << itr->second << std::endl;
    }
}

int map_main() {
    std::map<std::string, double> pitcher_list;

    // 참고로 2017년 7월 4일 현재 투수 방어율 순위입니다.

    // 맵의 insert 함수는 pair 객체를 인자로 받습니다.
    pitcher_list.insert(std::pair<std::string, double>("박세웅", 2.23));
    pitcher_list.insert(std::pair<std::string, double>("해커 ", 2.93));

    pitcher_list.insert(std::pair<std::string, double>("피어밴드 ", 2.95));

    // 타입을 지정하지 않아도 간단히 std::make_pair 함수로
    // std::pair 객체를 만들 수 도 있습니다.
    pitcher_list.insert(std::make_pair("차우찬", 3.04));
    pitcher_list.insert(std::make_pair("장원준 ", 3.05));
    pitcher_list.insert(std::make_pair("헥터 ", 3.09));

    // 혹은 insert 를 안쓰더라도 [] 로 바로
    // 원소를 추가할 수 있습니다.
    pitcher_list["니퍼트"] = 3.56;
    pitcher_list["박종훈"] = 3.76;
    pitcher_list["켈리"] = 3.90;

    print_map3(pitcher_list);

    std::cout << "박세웅 방어율은? :: " << pitcher_list["박세웅"] << std::endl;
    return 0;
}
int main() {
    // set_main();
    // set2_main();
    map_main();
}