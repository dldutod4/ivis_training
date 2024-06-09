#include <iostream>
#include <memory>

template <typename T>
class List {
    struct Node {
        std::shared_ptr<Node> next_node;
        T value;
    };

    // List의 맨 앞을 가르키는 head_ptr를 생성
    std::shared_ptr<Node> head_ptr = std::make_shared<Node>();

public:
    List() { head_ptr = NULL; };

    void show_list() {
        std::shared_ptr<Node> current_ptr = head_ptr;

        std::cout << "start of list >> ";
        // 맨 앞 헤드 포인터부터 뒤로 하나씩 이동하며 출력
        while (current_ptr != NULL) {
            std::cout << current_ptr->value << " ";
            current_ptr = current_ptr->next_node;
        }

        current_ptr.reset();
        std::cout << "<< end of list" << std::endl;
    }
    void push_back(T value) {
        // 새로운 노드를 생성 및 값 입력
        std::shared_ptr<Node> node = std::make_shared<Node>();
        node->value = value;

        // 헤드 포인터가 List 끝인 NULL을 가르키고 있을때
        if (head_ptr == NULL) {
            head_ptr = node;
            node->next_node = NULL;

        } else {
            std::shared_ptr<Node> old_ptr = head_ptr;

            // 헤드 포인터부터 맨 끝의 포인터까지 탐색
            while (old_ptr->next_node != NULL) {
                old_ptr = old_ptr->next_node;
            }

            // 맨 끝의 포인터의 다음 노드 포인터가 새로 생성된 노드의 포인터를 가르킨다.
            old_ptr->next_node = node;
            node->next_node = NULL;
            old_ptr.reset();
        }
    }
    void push_front(T value) {
        // 새로운 노드를 생성 및 값 입력
        std::shared_ptr<Node> node = std::make_shared<Node>();
        node->value = value;

        // 헤드 포인터가 List 끝인 NULL을 가르키고 있을때
        if (head_ptr == NULL) {
            head_ptr = node;
            node->next_node = NULL;

        } else {
            std::shared_ptr<Node> old_ptr = head_ptr;
            head_ptr = node;
            node->next_node = old_ptr;
            old_ptr.reset();
        }
    }
    T pop_back() {
        // List가 비어있으면 0 반환
        if (head_ptr == NULL) {
            std::cout << "Empty List" << std::endl;
            return 0;
        }

        std::shared_ptr<Node> current_ptr = head_ptr;
        std::shared_ptr<Node> front_ptr = NULL;

        // 맨 앞 헤드 포인터부터 뒤로 하나씩 이동하며 탐색
        while (current_ptr->next_node != NULL) {
            front_ptr = current_ptr;
            current_ptr = current_ptr->next_node;
        }

        if (current_ptr == head_ptr) {
            T result = head_ptr->value;
            head_ptr = NULL;
            return result;
        }

        T result = current_ptr->value;
        if (front_ptr != NULL) front_ptr->next_node = NULL;

        return result;
    }
    T pop_front() {
        // List가 비어있으면 0 반환
        if (head_ptr == NULL) {
            std::cout << "Empty List" << std::endl;
            return 0;
        }

        // 반환할 결과값을 result에 저장
        T result = head_ptr->value;
        head_ptr = head_ptr->next_node;

        // Q. 기존의 헤드 포인터가 가르키고 있던 노드의 다음 노드를 가르키는 shared_ptr을 해제해줘야 하는가?
        // A. 헤드 포인터가 더 이상 노드 포인터를 가르키지 않고 있으므로 해당 노드는 더 이상 누구의 참조도 받지 않는다.
        // 따라서 자동으로 해당 노드는 reset이 된다.

        return result;
    }
    std::shared_ptr<Node> search(T value) {
        // List가 비어있으면 0 반환
        if (head_ptr == NULL) {
            std::cout << "Empty List" << std::endl;
            return 0;
        }

        std::shared_ptr<Node> current_ptr = head_ptr;

        // 맨 앞 헤드 포인터부터 뒤로 하나씩 이동하며 탐색
        while (current_ptr->value != value && current_ptr->next_node != NULL) {
            current_ptr = current_ptr->next_node;
        }

        if (current_ptr->next_node == NULL && current_ptr->value != value) {
            std::cout << "List isn't containing " << value << std::endl;
            return NULL;
        } else {
            return current_ptr;
        }
    }
    void insert_back(T serach_value, T insert_value) {
        std::shared_ptr<Node> current_ptr = this->search(serach_value);
        std::shared_ptr<Node> node = std::make_shared<Node>();
        node->value = insert_value;

        node->next_node = current_ptr->next_node;
        current_ptr->next_node = node;
    }
    void remove(T value) {
        // List가 비어있으면 0 반환
        if (head_ptr == NULL) {
            std::cout << "Empty List" << std::endl;
        }

        std::shared_ptr<Node> current_ptr = head_ptr;
        std::shared_ptr<Node> front_ptr = NULL;

        // 맨 앞 헤드 포인터부터 뒤로 하나씩 이동하며 탐색
        while (current_ptr->next_node != NULL && current_ptr->value != value) {
            front_ptr = current_ptr;
            current_ptr = current_ptr->next_node;
        }

        // 맨 앞에서 부터 끝까지 탐색하였음에도 value를 찾지 못했을 경우
        if (current_ptr->next_node == NULL && current_ptr->value != value) {
            std::cout << "List isn't containing " << value << std::endl;
        } else {
            front_ptr->next_node = current_ptr->next_node;
        }
    }
    void clear_list() { head_ptr = NULL; }
};

int main() {
    List<int> l;
    l.push_back(1);
    l.push_front(2);
    l.push_back(3);
    l.push_front(4);
    l.show_list();

    std::cout << "find 3 at " << l.search(3) << std::endl;
    l.search(8);

    std::cout << "pop front " << l.pop_front() << std::endl;
    l.show_list();
    std::cout << "pop back " << l.pop_back() << std::endl;
    l.show_list();

    l.insert_back(2, 5);
    l.insert_back(1, 6);
    l.show_list();

    l.remove(1);
    l.show_list();

    l.clear_list();
    l.show_list();
    return 0;
}