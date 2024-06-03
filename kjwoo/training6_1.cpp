// string 클래스

#include <iostream>
#include <string>
class Employee
{
    std::string name;
    int age;

    std::string position; // 직책 (이름)
    int rank;             // 순위 (값이 클 수록 높은 순위)

public:
    Employee(std::string name, int age, std::string position, int rank)
        : name(name), age(age), position(position), rank(rank) {}

    // 복사 생성자
    Employee(const Employee &employee)
    {
        name = employee.name;
        age = employee.age;
        position = employee.position;
        rank = employee.rank;
    }

    // 디폴트 생성자
    Employee() {}

    void print_info()
    {
        std::cout << name << " (" << position << " , " << age << ") ==> "
                  << calculate_pay() << "만원" << std::endl;
    }
    int calculate_pay() { return 200 + rank * 50; }
};
class Manager
{
    std::string name;
    int age;

    std::string position; // 직책 (이름)
    int rank;             // 순위 (값이 클 수록 높은 순위)
    int year_of_service;

public:
    Manager(std::string name, int age, std::string position, int rank,
            int year_of_service)
        : year_of_service(year_of_service),
          name(name),
          age(age),
          position(position),
          rank(rank) {}

    // 복사 생성자
    Manager(const Manager &manager)
    {
        name = manager.name;
        age = manager.age;
        position = manager.position;
        rank = manager.rank;
        year_of_service = manager.year_of_service;
    }

    // 디폴트 생성자
    Manager() {}

    int calculate_pay() { return 200 + rank * 50 + 5 * year_of_service; }
    void print_info()
    {
        std::cout << name << " (" << position << " , " << age << ", "
                  << year_of_service << "년차) ==> " << calculate_pay() << "만원"
                  << std::endl;
    }
};
class EmployeeList
{
    int alloc_employee; // 할당한 총 직원 수

    int current_employee; // 현재 직원 수
    int current_manager;  // 현재 매니저 수

    Employee **employee_list; // 직원 데이터
    Manager **manager_list;   // 매니저 데이터

public:
    EmployeeList(int alloc_employee) : alloc_employee(alloc_employee)
    {
        employee_list = new Employee *[alloc_employee];
        manager_list = new Manager *[alloc_employee];

        current_employee = 0;
        current_manager = 0;
    }
    void add_employee(Employee *employee)
    {
        // 사실 current_employee 보다 alloc_employee 가 더
        // 많아지는 경우 반드시 재할당을 해야 하지만, 여기서는
        // 최대한 단순하게 생각해서 alloc_employee 는
        // 언제나 current_employee 보다 크다고 생각한다.
        // (즉 할당된 크기는 현재 총 직원수 보다 많음)
        employee_list[current_employee] = employee;
        current_employee++;
    }
    void add_manager(Manager *manager)
    {
        manager_list[current_manager] = manager;
        current_manager++;
    }
    int current_employee_num() { return current_employee + current_manager; }

    void print_employee_info()
    {
        int total_pay = 0;
        for (int i = 0; i < current_employee; i++)
        {
            employee_list[i]->print_info();
            total_pay += employee_list[i]->calculate_pay();
        }
        for (int i = 0; i < current_manager; i++)
        {
            manager_list[i]->print_info();
            total_pay += manager_list[i]->calculate_pay();
        }
        std::cout << "총 비용 : " << total_pay << "만원 " << std::endl;
    }
    ~EmployeeList()
    {
        for (int i = 0; i < current_employee; i++)
        {
            delete employee_list[i];
        }
        for (int i = 0; i < current_manager; i++)
        {
            delete manager_list[i];
        }
        delete[] employee_list;
        delete[] manager_list;
    }
};

// 상속이 필요
// 기반 클래스
class Base
{
    protected:
    std::string BaseS;

public:
    Base() : BaseS("기반") { std::cout << "기반 클래스" << std::endl; }

    void what() { std::cout << BaseS<< std::endl; }
};
// 파생 클래스
class Derived : public Base //상속받을때 기반클래스의 멤버들을 처리할 방식을 의미
//public -> 그대로
//protected -> public을 protected로 전환
//private -> 모두 private
{
    std::string s;

public:
    Derived() : Base(), s("파생")
    { // 기반 생성자가 먼저 실행되고이후에 파생 생성자가 실행된다.
        // 기반생성자를 명시안하면 디폴트생성자가 호출된다.
        std::cout << "파생 클래스" << std::endl;

        // Base 에서 what() 을 물려 받았으므로
        // Derived 에서 당연히 호출 가능하다
        what();
    }
    void what(){ //함수 오버라이딩
        std::cout << s <<std::endl;
        std::cout << BaseS<<std::endl; //privated은 파생클래스에서도 접근이 불가하다. 
        //protected는 파생클래스가 접근할 수있다.
    }
};

int main()
{
    std::cout << "== 기반 클래스 생성 ==" << std ::endl;
    Base p;
    std::cout << "== 파생 클래스 생성 ==" << std::endl;
    Derived c;
    return 0;
}