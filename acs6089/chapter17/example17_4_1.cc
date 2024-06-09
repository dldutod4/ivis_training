#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

int main() {
    std::filesystem::path p("./some_file");

    std::cout << "Does " << p << " exist? [" << std::boolalpha << std::filesystem::exists(p) << "]" << std::endl;
    std::cout << "Is " << p << " file? [" << std::filesystem::is_regular_file(p) << "]" << std::endl;
    std::cout << "Is " << p << " directory? [" << std::filesystem::is_directory(p) << "]" << std::endl;

    std::cout << "내 현재 경로 : " << fs::current_path() << std::endl;
    std::cout << "상대 경로 : " << p.relative_path() << std::endl;
    std::cout << "절대 경로 : " << fs::absolute(p) << std::endl;
    std::cout << "공식적인 절대 경로 : " << fs::canonical(p) << std::endl;

    fs::directory_iterator itr(fs::current_path() / "a");
    while (itr != fs::end(itr)) {
        const fs::directory_entry& entry = *itr;
        std::cout << entry.path() << std::endl;
        itr++;
    }

    for (const fs::directory_entry& entry : fs::recursive_directory_iterator(fs::current_path() / "a")) {
        std::cout << entry.path() << std::endl;
    }
}