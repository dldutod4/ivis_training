#include <algorithm>
#include <chrono>
#include <future>
#include <iostream>
#include <thread>
#include <vector>

namespace ch = std::chrono;

int main() {
    // SIZE 크기의 행렬 생성
    const int SIZE = 100000;
    std::vector<int> a;
    for (size_t i = 0; i < SIZE; i++) {
        a.push_back(SIZE - i);
    }

    // 탐색 시작 틱 저장
    ch::time_point<ch::high_resolution_clock> start = ch::high_resolution_clock::now();

    // 단일 쓰레드로 탐색
    std::vector<int>::iterator ptr = std::find(a.begin(), a.end(), 100);

    // 탐색 종료 틱 저장
    ch::time_point<ch::high_resolution_clock> end = ch::high_resolution_clock::now();

    // 탐색에 걸린 틱 계산
    auto diff = end - start;

    std::cout << *ptr << std::endl;

    // 탐색에 걸린 틱을 us단위로 변환
    std::cout << "To find num at sync " << ch::duration_cast<ch::microseconds>(diff).count() << "us" << std::endl;

    // 탐색 시작 틱 저장
    start = ch::high_resolution_clock::now();

    // 쓰레드를 하나 더 배정해 처음부터 중간 부분을 탐색
    std::future<std::vector<int>::iterator> f1 =
        std::async([&a]() { return std::find(a.begin(), a.begin() + a.size() / 2, 100); });

    // 원래 있던 쓰레드에서 중간 + 1 부터 끝까지 탐색
    ptr = std::find(a.begin() + a.size() / 2 + 1, a.end(), 100);

    // 반환된 포인터의 상태를 보고 탐색이 잘 됐는지 판단
    if (ptr == a.end()) ptr = f1.get();
    if (ptr == a.begin() + a.size() / 2) ptr = a.end();

    // 탐색 종료 틱 저장
    end = ch::high_resolution_clock::now();

    // 탐색에 걸린 틱 계산
    diff = end - start;

    std::cout << *ptr << std::endl;

    // 탐색에 걸린 틱을 us단위로 변환
    std::cout << "To find num at async " << ch::duration_cast<ch::microseconds>(diff).count() << "us" << std::endl;
    return 0;
}