#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
    std::unordered_map<std::string, int> m = {{"a", 1}, {"b", 2}, {"c", 3}};

    std::vector<std::string> keys;

    // map m 객체에서 key 값들만 빼서 string vector keys 객체에 저장
    for (const auto& [k, v] : m) {
        keys.push_back(k);
    }

    for (const auto& s : keys) {
        std::cout << s << std::endl;
    }
}