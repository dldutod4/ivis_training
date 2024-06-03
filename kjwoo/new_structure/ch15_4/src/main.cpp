#include <future>
#include <iostream>
#include <thread>

int do_work(int x) {
    // x 를 가지고 무슨 일을 한다.
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return x;
}

void do_work_parallel() {
    auto f1 = std::async([]() { return do_work(3); });
    auto f2 = std::async([]() { return do_work(3); });

    std::future<int> f3 = std::async(std::launch::deferred, do_work, 3);
    do_work(3);

    f1.get();
    f2.get();
    // f3.get();
}

void do_work_sequential() {
    do_work(3);
    do_work(3);
    do_work(3);
}

int main() { do_work_parallel(); }