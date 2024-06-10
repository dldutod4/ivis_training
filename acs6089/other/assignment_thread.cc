#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

int prime_number(const int th_num, const int num, std::mutex& m, std::ofstream& file) {
    // 입력된 숫자가 2보다 작으면 소수를 카운팅 할 수 없다
    if (num < 2) {
        std::cout << "input number must be bigger than 1" << std::endl;
        return 1;
    }

    // 출력 문장
    std::string str = "thread[" + std::to_string(th_num);
    str += "] finished. prime numbers between 0 and " + std::to_string(num) + " are ";

    int result = 0;
    std::vector<bool> arr(num + 1, true);
    arr[0] = false;
    arr[1] = false;

    // 소수들을 찾는다.
    for (size_t i = 2; i <= num; i++) {
        if (arr[i] == true) {
            for (size_t j = 2; j * i <= num; j++) {
                arr[i * j] = false;
            }
        }
    }

    // 소수들을 카운팅한다.
    for (size_t i = 2; i <= num; i++) {
        if (arr[i] == true) result++;
    }
    str += std::to_string(result) + "\n";

    // 결과값을 파일에 쓴다.
    // 파일을 쓰는 동안 다른 쓰레드가 접근하지 못하도록 뮤텍스로 관리한다.
    m.lock();
    file << str;
    m.unlock();

    return 0;
}

int main(int argc, char* argv[]) {
    std::ofstream log1("log1.txt");
    std::ofstream log2("log2.txt");

    std::mutex m1;
    std::mutex m2;

    std::vector<std::thread> th;

    for (size_t i = 1; i < argc; i++) {
        int input = atoi(argv[i]);
        if (argc / 2 > (i - 1))
            th.push_back(std::thread(prime_number, i, input, std::ref(m1), std::ref(log1)));
        else
            th.push_back(std::thread(prime_number, i, input, std::ref(m2), std::ref(log2)));
    }

    for (size_t i = 0; i < argc - 1; i++) {
        th[i].join();
    }

    return 0;
}