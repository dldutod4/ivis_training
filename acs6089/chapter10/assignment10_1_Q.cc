#include <iostream>
#include <vector>

template <typename T>
class deque {
    int vector_size = 3;
    std::vector<T>* blocks;
    std::vector<T>* blocks_itr;
    std::vector<T>* blocks_begin;

public:
    deque() {
        blocks = new std::vector<T>[10];
        blocks_itr = blocks;
        blocks_begin = blocks;
    }
    ~deque() { delete[] blocks; }

    void push_back(T a) {
        // block에 할당된 크기를 초과할 시에 새로운 블록을 생성
        if (blocks_itr->size() == vector_size) {
            std::cout << "new block" << std::endl;
            blocks_itr++;
            blocks_itr->push_back(a);
        } else {
            blocks_itr->push_back(a);
        }
    }

    void show() {
        for (size_t i = 0; i < 10; i++) {
            int current_vector_size = (blocks_begin + i)->size();
            std::vector<T> s = blocks[i];
            std::cout << i << " block" << std::endl;
            for (size_t j = 0; j < current_vector_size; j++) {
                std::cout << s[j] << std::endl;
            }
            if (blocks_begin + i == blocks_itr) break;
        }
    }
};

int main() {
    deque<int> d;
    for (size_t i = 0; i < 20; i++) {
        d.push_back(i);
    }
    d.show();
}