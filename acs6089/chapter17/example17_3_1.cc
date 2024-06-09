#include <iomanip>
#include <iostream>
#include <map>
#include <random>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dist(/* 평균 = */ 0, /* 표준 편차 = */ 1);

    std::map<int, int> hist{};
    for (int n = 0; n < 10000; ++n) {
        ++hist[std::round(dist(gen))];
    }
    for (auto p : hist) {
        std::cout << std::setw(2) << p.first << ' ' << std::string(p.second / 100, '*') << " " << p.second << '\n';
    }
}