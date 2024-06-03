//  문제 1

// std::atomic<bool> 을 사용해서 lock() 과 unlock() 을 만들어보세요.
// 참고로 compare_exchange_strong 함수를 사용하는 것이 도움이 됩니다.
// compare_exchange_strong 은 아래와 같이 생겼습니다.

// bool compare_exchange_strong(
//   T& expected, T desired, std::memory_order order = std::memory_order_seq_cst);

// 만일 현재 atomic 객체의 값이 expected 와 같다면 desired 로 바꾸고 true 를 리턴합니다.
// expected 와 다르다면 desired 로 바꾸지 않고 그냥 false 를 리턴합니다.
// 물론 이 읽기 - 수정하기 - 쓰기 명령은 atomic 하게 실행됩니다.
#include <atomic>
#include <iostream>
#include <thread>
/*
bool check가 false일 때
task가 check를 true로 바꾸고
연산을 해야함.

*/
std::atomic<bool> check(false);
void lock() {
    bool flag = false;
    while (!check.compare_exchange_strong(flag, true, std::memory_order_acquire)) {
        // check가 false였다면 통과시키고 true로 바꾼다.
        flag = false;
    }
}
void unlock() { check.store(false, std::memory_order_acquire); }

void worker1(int& counter) {
    for (int i = 0; i < 5000; i++) {
        lock();
        counter++;
        // std::cout << "w1:" << counter << std::endl;
        unlock();
    }
}
void worker2(int& counter) {
    for (int i = 0; i < 5000; i++) {
        lock();
        counter++;
        // std::cout << "w2:" << counter << std::endl;
        unlock();
    }
}
int main() {
    int counter = 0;
    check.store(false, std::memory_order_seq_cst);
    std::thread t1(worker1, std::ref(counter));
    std::thread t2(worker2, std::ref(counter));
    // 바인드함수로 인자가 복사돼서 전달되기때문에 레퍼런스가 아니라 복사값이 들어가서
    // ref함수로 명시해야한다.

    t1.join();
    t2.join();
    std::cout << counter;
}