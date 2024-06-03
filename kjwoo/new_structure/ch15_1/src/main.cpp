#include <cstdio>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>
using std::thread;
using std::vector;
void func1() {
    for (int i = 0; i < 10; i++) {
        std::cout << "쓰레드 1 작동중! \n";
    }
}

void func2() {
    for (int i = 0; i < 10; i++) {
        std::cout << "쓰레드 2 작동중! \n";
    }
}

void func3() {
    for (int i = 0; i < 10; i++) {
        std::cout << "쓰레드 3 작동중! \n";
    }
}
int join_main() {
    thread t1(func1);  // 스레드 객체를 생성하면 인자로 전달받은 함수르 실행하게 됩니다.
    thread t2(func2);
    thread t3(func3);

    // t1.join();  // 스레드의 실행이 끝나면 join()이 리턴된다.
    // t2.join();
    // t3.join();
    return 0;
}
int detach_main() {
    thread t1(func1);
    thread t2(func2);
    thread t3(func3);

    t1.detach();  // detach를 하면 main함수는 더이상 스레드들이 종료될 때까지 기다리지 않음.
    t2.detach();
    t3.detach();

    std::cout << "메인 함수 종료 \n";
    return 0;
}

void worker(vector<int>::iterator start, vector<int>::iterator end, int* result) {
    int sum = 0;
    for (auto itr = start; itr < end; ++itr) {
        sum += *itr;
    }
    *result = sum;

    // 쓰레드의 id 를 구한다.
    thread::id this_id = std::this_thread::get_id();
    printf("쓰레드 %x 에서 %d 부터 %d 까지 계산한 결과 : %d \n", this_id, *start, *(end - 1), sum);
}

int sum_main() {
    vector<int> data(10000);
    for (int i = 0; i < 10000; i++) {
        data[i] = i;
    }

    // 각 쓰레드에서 계산된 부분 합들을 저장하는 벡터
    vector<int> partial_sums(4);

    vector<thread> workers;
    for (int i = 0; i < 4; i++) {
        workers.push_back(thread(worker, data.begin() + i * 2500, data.begin() + (i + 1) * 2500, &partial_sums[i]));
    }

    for (int i = 0; i < 4; i++) {
        workers[i].join();
    }

    int total = 0;
    for (int i = 0; i < 4; i++) {
        total += partial_sums[i];
    }
    std::cout << "전체 합 : " << total << std::endl;
    return 0;
}

void worker2(int& counter) {
    for (int i = 0; i < 10000; i++) {
        counter += 1;
    }
}

int cnt_main() {
    int counter = 0;

    vector<thread> workers;
    for (int i = 0; i < 4; i++) {
        // 레퍼런스로 전달하려면 ref 함수로 감싸야 한다 (지난 강좌 bind 함수 참조)
        workers.push_back(thread(worker2, std::ref(counter)));
    }

    for (int i = 0; i < 4; i++) {
        workers[i].join();
    }

    std::cout << "Counter 최종 값 : " << counter << std::endl;
    return 0;
}
int main() {
    // join_main();
    // detach_main();
    // sum_main();
    cnt_main();
}