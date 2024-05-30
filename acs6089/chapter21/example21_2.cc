#include <algorithm>
#include <iostream>
#include <set>

int main() {
    std::set<int> s = {1, 2, 3, 4, 5, 6, 7};

    for (auto itr = s.begin(), last = s.end(); itr != last;) {
        // itr이 가르키는 인자가 홀수이면 해당 인자를 삭제
        if (*itr % 2 == 1) {
            itr = s.erase(itr);
        } else {
            ++itr;
        }
    }

    for (auto& i : s) {
        std::cout << i << std::endl;
    }
}