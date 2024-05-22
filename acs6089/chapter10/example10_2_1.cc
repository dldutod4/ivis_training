#include <iostream>
#include <map>
#include <string>

template <typename K, typename V>
//map<K,V>의 주소를 넘긴다
void print_map(std::map<K,V>& m)
{
    for (auto i = m.begin(); i != m.end(); ++i)
    {
        std::cout << i->first << " " << i->second << std::endl;
    }
}

int main()
{
    std::map<std::string, double> list;

    list.insert(std::pair<std::string, double>("박세웅", 2.2));
    list.insert(std::pair<std::string, double>("류현진", 2.8));
    list.insert(std::make_pair("가나다", 1.2));
    list["라마바"]=5.6;

    print_map(list);
}