#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

std::atomic<bool> flag(true);
class new_mutex {
public:
    void lock(int& num) {
        bool expected = true;

        // mutex 권한을 획득한 쓰레드 표시
        if (flag.compare_exchange_strong(expected, false, std::memory_order_seq_cst))
            std::cout << num << " locking" << std::endl;

        // mutex 권한을 획득하지 못하고 대기하는 쓰레드 표시
        // 권한을 획득할 때까지 스스로를 호출
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(2));
            std::cout << num << " wait" << std::endl;
            lock(num);
        }
    }
    void unlock() {
        bool expected = false;

        // 사용을 끝낸 쓰레드는 mutex 권한을 반납
        if (flag.compare_exchange_strong(expected, true, std::memory_order_seq_cst)) std::cout << "unlock" << std::endl;

        // 잘못된 사용시 출력
        else {
            std::cout << "wrong use about unlock or lock" << std::endl;
        }
    }
};

void add1(int& n) {
    for (size_t i = 0; i < 100000; i++) {
        n++;
    }
}

void add2(int& n, new_mutex& m, int num) {
    m.lock(num);
    for (size_t i = 0; i < 100000; i++) {
        n++;
    }
    std::cout << num << " finished" << std::endl;
    m.unlock();
}

int main() {
    int a = 0;
    int b = 0;
    new_mutex m;

    std::thread t1(add1, std::ref(a));
    std::thread t2(add1, std::ref(a));

    t1.join();
    t2.join();

    std::cout << "no mutex output : " << a << std::endl;

    std::thread t3(add2, std::ref(b), std::ref(m), 1);
    std::thread t4(add2, std::ref(b), std::ref(m), 2);
    std::thread t5(add2, std::ref(b), std::ref(m), 3);

    t3.join();
    t4.join();
    t5.join();

    std::cout << "mutex output : " << b << std::endl;

    return 0;
}