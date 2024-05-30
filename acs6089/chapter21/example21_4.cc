#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <string_view>

void ReplaceAll(std::string& src, std::string_view from, std::string_view to) {
    size_t current = 0;
    while ((current = src.find(from, current)) != std::string::npos) {
        src.replace(current, from.size(), to);
        current += to.size();
    }
}

int main() {
    std::string s = "I believe I can fly I believe I can fly I believe I can fly (woo)";
    std::cout << s << std::endl;

    ReplaceAll(s, "fly", "code");
    std::cout << s << std::endl;

    std::string needle = "believe";

    // 평균 시간 복잡도 O(N)인 문자열 탐색기 boyer_moore_searcher
    auto it = std::search(s.begin(), s.end(), std::boyer_moore_searcher(needle.begin(), needle.end()));

    if (it != s.end()) {
        std::cout << needle << " found at " << std::distance(s.begin(), it) << std::endl;
    } else {
        std::cout << needle << " not found " << std::endl;
    }

    // 문자열 내의 모든 문자를 소문자로 사용
    std::transform(s.begin(), s.end(), s.begin(), [](char c) { return std::tolower(c); });
    std::cout << s << std::endl;
}