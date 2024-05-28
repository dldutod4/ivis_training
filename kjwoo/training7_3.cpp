// #include<fstream>
// #include<iostream>
// #include<string>

// int main(){
//     std::ifstream in("test.txt"); //스트림 생성시 경로 설정후 열게됨
//     //자동적으로 소멸자가 close를 해주기때문에 close를 할필요가 없다. 그치만 직접해야하는 경우도있다.
//     //같은 객체로 다른 파일과 새롭게 연결할 때는 close를 하고 새로 open해주어야한다.
//     std::string s;

//     if (in.is_open()) //스트림이 열렸는지 확인.
//     {
//         in >> s;
//         std::cout <<"입력받은 문자열 ::" << s << std::endl;
//         /* code */
//     }
//     else{
//         std::cout<<"파일을 찾을 수 없습니다!"<< std::endl;
//     }
//     char peek = in.rdbuf()->snextc();
//     std::cout<<"snextc()::"<<peek<<std::endl;
//     return 0;

// }

// #include <fstream>
// #include <iostream>
// #include <string>

// int main() {
//   // 파일 읽기 준비
//   std::ifstream in("test.txt", std::ios::binary); //바이너리형태로 받는다.
//   std::string s;

//   int x;
//   if (in.is_open()) {
//     in.read((char*)(&x), 4); //4바이트의 int를 char[4] 배열로 인식시킨후 x에 파일로부터 읽어온 값을 넣는다.
//     //꼭 몇바이트를 읽을지 두번째 인자로 넣어야한다.
//     std::cout << std::hex << x << std::endl;
//   } else {
//     std::cout << "파일을 찾을 수 없습니다!" << std::endl;
//   }

//   return 0;
// }

// 파일 전체 읽기

// #include <fstream>
// #include <iostream>
// #include <string>

// int main() {
//   // 파일 읽기 준비
//   std::ifstream in("test.txt");
//   std::string s;

//   if (in.is_open()) {
//     // 위치 지정자를 파일 끝으로 옮긴다.
//     in.seekg(0, std::ios::end); //파일위치 지정자를 움직이는 함수 seekg 2번째인자로부터 0만큼떨어진것
//     //즉 파일끝에서 0만큼떨어졌으니 파일 끝이다.

//     // 그리고 그 위치를 읽는다. (파일의 크기)
//     int size = in.tellg(); //tellg 파일 시작점에서 위치지정자까지의 위치를 반환. 파일크기를 구한다.

//     // 그 크기의 문자열을 할당한다.
//     s.resize(size);

//     // 위치 지정자를 다시 파일 맨 앞으로 옮긴다.
//     in.seekg(0, std::ios::beg);

//     // 파일 전체 내용을 읽어서 문자열에 저장한다.
//     in.read(&s[0], size);
//     std::cout << s << std::endl;
//   } else {
//     std::cout << "파일을 찾을 수 없습니다!" << std::endl;
//   }

//   return 0;
// }

// // getline 으로 읽어들이기
// #include <fstream>
// #include <iostream>
// #include <string>

// int main() {
//   // 파일 읽기 준비
//   std::ifstream in("test.txt");
//   char buf[100];
//   std::string s;

//   if (!in.is_open()) {
//     std::cout << "파일을 찾을 수 없습니다!" << std::endl;
//     return 0;
//   }

//   while (in) {
//     //in.getline(buf, 100); //ifstream의 getline함수는 지정문자가 나오기전에 버퍼가 다치면 fail비트를 킨다.
//     getline(in,s); // string의 getline함수를 이용하면 버퍼크기를 지정안해도 알아서 지정문자나 파일끝까지 입력을 받는다.
//     std::cout << buf << std::endl;
//   }

//   return 0;
// }
/*
주의 사항 while조건으로 in.eof()를 사용해서는 안됩니다.
eof함수는 파일위치 지시자가 파일끝에 도달한 이후에 true를 리턴하기 때문에
파일끝 바로직전까지 읽어도 true가 되는데 그상태에서 읽으면 아무것도 읽히지 않게됩니다.
in.eof()는 파일읽기가 안전하다는 것을 보장하지않으며 while(in)처럼 객체 자체를 전달해야
다음읽기가 안전할때만 true가 됩니다.
*/

// #include <iostream>
// #include <fstream>
// #include <string>

// int main()
// {
//     // 파일 쓰기 준비
//     // std::ofstream out("test.txt");//파일내용이 다 지워지고 새로 덮어쓴다.
//     std::ofstream out("test.txt", std::ios::app); // app을 전달하면 뒤에 덧붙여쓴다.
//     // 그외에도 ate,trunc,in,out이 있는데 trunc는 기본설정으로 모든내용이 지워지고,
//     // ate는 파일끝에서 부터 읽기쓰기를 하지만 위치지정자를 이전으로 옮길 수 있어
//     // 원래 내용을 보장하지 않는다.
//     // in, out은 입력인지 출력인지를 설정하며 ofstream,ifstream 생성시 이미 설정되어있다.

//     std::string s;
//     if (out.is_open())
//     {
//         out << "이걸 쓰자~~";
//     }

//     return 0;
// }

// #include <fstream>
// #include <iostream>
// #include <string>

// class Human
// {
//     std::string name;
//     int age;

// public:
//     Human(const std::string &name, int age) : name(name), age(age) {}
//     std::string get_info()
//     {
//         return "Name :: " + name + " / Age :: " + std::to_string(age);
//     }

//     friend std::ofstream &operator<<(std::ofstream &o, Human &h);
// };

// std::ofstream &operator<<(std::ofstream &o, Human &h)
// {
//     o << h.get_info();
//     return o;
// }
// int main()
// {
//     // 파일 쓰기 준비
//     std::ofstream out("test.txt");

//     Human h("이재범", 60);
//     out << h << std::endl;

//     return 0;
// }

#include <iostream>
#include <sstream>
#include <string>
double to_number(std::string s)
{
  std::istringstream ss(s);
  double x;

  ss >> x;
  return x;
}
std::string to_str(int x)
{
  std::ostringstream ss;
  ss << x;

  return ss.str();
}
int main()
{
  std::istringstream ss("123"); // 문자열을 스트림처럼 사용하게 해주는 가상화장치
  int x;
  ss >> x;

  std::cout << "입력 받은 데이터 :: " << x << std::endl;

  return 0;
}
