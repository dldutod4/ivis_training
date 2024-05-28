#include <iostream>
#include <vector>
template <typename T>
class deque2 {
    T** block_addresses;

    T* begin_itr;
    T* end_itr;
    int begin_block;
    int end_block;
    int begin_idx;
    int end_idx;

public:
    deque2() {
        std::cout << "생성" << std::endl;
        block_addresses = new T*[10];  // 총 10블록으로 고정. 블록 끝까지 도달했을때 블록을 추가하는 기능은 구현x
        for (int i = 0; i < 10; i++) {
            block_addresses[i] = new T[10];  // 블록당 10개의 데이터 보관
        }
        begin_itr =
            &block_addresses[3]
                            [9];  // 중간인 [3][9]부터 사용하기로 설정(push_front와 push_back을 위해 공간을 앞뒤로 남김)
        end_itr = &block_addresses[3][9];
        begin_block = 3;
        end_block = 3;
        begin_idx = 9;
        end_idx = 9;
    }
    void push_back(T inp) {
        if (end_idx == 9) {  // 블록끝도달시 다음블록으로
            *end_itr = inp;
            end_idx = 0;
            end_block++;
            end_itr = &block_addresses[end_block][0];
        } else {
            *end_itr = inp;
            end_itr++;
            end_idx++;
        }
    }
    void push_front(T inp) {
        if (begin_idx == 0) {  // 블록 시작도달시 이전블록으로
            begin_idx = 9;
            begin_block--;
            begin_itr = &block_addresses[begin_block][9];
            *begin_itr = inp;
        } else {
            begin_itr--;
            begin_idx--;
            *begin_itr = inp;
        }
    }
    T front() { return *begin_itr; }
    T back() {
        // end는 마지막 원소 뒤를 가리키므로 주소를 앞으로 땡겨서 반환.
        if (end_idx == 0) {
            return block_addresses[end_block - 1][9];
        } else {
            return *(end_itr - 1);
        }
    }
    T* begin() { return begin_itr; }
    T* end() { return end_itr; }
    T at(int idx) {
        int blk_num = begin_block;
        int blk_idx = begin_idx;
        for (int i = 0; i < idx; i++) {
            if (idx == 9) {
                blk_num++;
                blk_idx = 0;
            } else
                blk_idx++;
        }

        return block_addresses[blk_num][blk_idx];
    }
};

int main() {
    deque2<int>* dqueint = new deque2<int>();
    deque2<double>* dquedouble = new deque2<double>();

    dqueint->push_back(12);
    dqueint->push_back(20);
    dqueint->push_front(10);

    dquedouble->push_front(9.9);
    dquedouble->push_front(7.7);
    dquedouble->push_back(5.5);

    std::cout << "dqueint's front:" << dqueint->front() << std::endl
              << "dqueint's back:" << dqueint->back() << std::endl;
    std::cout << "dquedouble's front:" << dquedouble->front() << std::endl
              << "dquedouble's back:" << dquedouble->back() << std::endl;

    return 0;
}