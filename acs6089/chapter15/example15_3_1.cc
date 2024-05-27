#include <atomic>
#include <iostream>
#include <thread>

std::atomic<int> atomic_value(0);

void compare_exchange_example() {
    int expected = 0;
    int desired = 1;
    if (atomic_value.compare_exchange_strong(expected, desired)) {
        std::cout << "Exchange successful: " << atomic_value << std::endl;
    } else {
        std::cout << "Exchange failed. Expected: " << expected << ", Actual: " << atomic_value << std::endl;
    }
}

int main() {
    std::thread t1(compare_exchange_example);
    std::thread t2(compare_exchange_example);

    t1.join();
    t2.join();

    return 0;
}