#include <algorithm>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

std::vector<int>::iterator find_thread(const std::vector<int>& v, const int& find_thread_num, const int& find_num) {}

int main() {
    const int SIZE = 1000;
    const int find_thread_number = 4;
    std::vector<int> a;
    for (size_t i = 0; i < SIZE; i++) {
        a.push_back(i + 1);
    }

    std::vector<int>::iterator ptr = std::find(a.begin(), a.end(), 100);

    std::cout << *ptr << std::endl;

    return 0;
}