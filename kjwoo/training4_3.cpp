// /*
// 복사생성자 -깊은 복사와 얕은 복사
// 소멸자

// */
// #include<iostream>
// #include<string.h>
// class Marine{
//     int hp;
//     int coord_x, coord_y;
//     int damage;
//     bool is_dead;
//     char* name;

//     public:
//     Marine();
//     Marine(int x, int y);
//     Marine(int x, int y, const char* marine_name);
//     ~Marine(); //소멸자는 인자를 가지지 않는다.

//     int attack();
//     void be_attacked(int damage_earn);
//     void move(int x, int y);

//     void show_status();

// };

// Marine::Marine(){
//     name =NULL;
//     hp=50;
//     coord_x=coord_y=0;
//     damage = 5;
//     is_dead = false;
// }
// Marine::Marine(int x, int y){
//     coord_x = x;
//     coord_y = y;
//     hp =50;
//     damage=5;
//     is_dead = false;
//     name = NULL;
// }
// Marine::Marine(int x, int y, const char* marine_name){
//     name = new char[strlen(marine_name)+1]; //동적으로 생성한 char 배열 -> 객체가 삭제돼도 없어지지않는다. ->소멸자필요
//     strcpy(name,marine_name);

//     coord_x = x;
//     coord_y = y;
//     hp = 50;
//     damage = 5;
//     is_dead = false;
// }
// void Marine:: move(int x, int y){
//     coord_x = x;
//     coord_y = y;
// }

// void Marine::show_status(){
//     std::cout <<"*** Marine *** " << std::endl;
//     std::cout <<" Location :( " << coord_x << " , " << coord_y << " ) " << std::endl;
//     std::cout << " HP : " << hp << std::endl;
// }
// int Marine::attack(){ return damage;}
// void Marine::be_attacked(int damage_earn){
//     hp-= damage_earn;
//     if(hp <= 0) is_dead =true;
// }
// Marine::~Marine(){
//     std::cout << name <<"소멸자의 호출" << std::endl;
//     if(name != NULL){
//         delete[] name; //배열동적할당엔 delete[]
//     }
// }
// int main(){
//     // Marine marine1(2, 3);
//     // Marine marine2(3, 5);

//     // marine1.show_status();
//     // marine2.show_status();

//     // std::cout << std::endl << "마린 1 이 마린 2 를 공격! " << std::endl;
//     // marine2.be_attacked(marine1.attack());
//     // marine1.show_status();
//     // marine2.show_status();

//     // 객체를 배열로 사용
//     // Marine* marines[100];
//     // marines[0] = new Marine(2,3); // malloc과 달리 new는 생성자도 동시에 호출해 준다.
//     // marines[1] = new Marine(3,5);

//     // marines[0]->show_status();
//     // marines[1]->show_status();
//     // std::cout <<std::endl << "마린 1이 마린 2를 공격" <<std::endl;

//     // marines[0]->be_attacked(marines[1]->attack());

//     // marines[0]->show_status();
//     // marines[1]->show_status();

//     // delete marines[0];
//     // delete marines[1];
//     // Marine* marines[100];

//     // marines[0] = new Marine(2, 3, "Marine 2");
//     // marines[1] = new Marine(1, 5, "Marine 1");

//     // marines[0]->show_status();

//     // std::cout << std::endl << "마린 1 이 마린 2 를 공격! " << std::endl;

//     // marines[0]->be_attacked(marines[1]->attack());

//     // marines[0]->show_status();
//     // marines[1]->show_status();

//     // delete marines[0];
//     // delete marines[1];

// }
// 복사 생성자의 중요성
// #include <string.h>
// #include <iostream>

// class Photon_Cannon
// {
//     int hp, shield;
//     int coord_x, coord_y;
//     int damage;

//     char *name;

// public:
//     Photon_Cannon(int x, int y);
//     Photon_Cannon(int x, int y, const char *cannon_name);
//     Photon_Cannon(const Photon_Cannon &pc);
//     ~Photon_Cannon();

//     void show_status();
// };
// Photon_Cannon::Photon_Cannon(int x, int y)
// {
//     hp = shield = 100;
//     coord_x = x;
//     coord_y = y;
//     damage = 20;

//     name = NULL;
// }
// Photon_Cannon::Photon_Cannon(const Photon_Cannon &pc)
// {
//     std::cout << "복사 생성자 호출! " << std::endl;
//     hp = pc.hp;
//     shield = pc.shield;
//     coord_x = pc.coord_x;
//     coord_y = pc.coord_y;
//     damage = pc.damage;

//     name = new char[strlen(pc.name) + 1];
//     strcpy(name, pc.name);
// }
// Photon_Cannon::Photon_Cannon(int x, int y, const char *cannon_name)
// {
//     hp = shield = 100;
//     coord_x = x;
//     coord_y = y;
//     damage = 20;

//     name = new char[strlen(cannon_name) + 1];
//     strcpy(name, cannon_name);
// }
// Photon_Cannon::~Photon_Cannon()
// {
//     if (name)
//         delete[] name;
// }
// void Photon_Cannon::show_status()
// {
//     std::cout << "Photon Cannon :: " << name << std::endl;
//     std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
//               << std::endl;
//     std::cout << " HP : " << hp << std::endl;
// }
// int main()
// {
//     Photon_Cannon pc1(3, 3, "Cannon");
//     Photon_Cannon pc2 = pc1;

//     pc1.show_status();
//     pc2.show_status();
// }

#include <iostream>
#include <string.h>

class string
{
    char *str;
    int len;

public:
    string(char c, int n); // 문자 c 가 n 개 있는 문자열로 정의
    string(const char *s);
    string(const string &s);
    ~string();

    void add_string(const string &s);  // str 뒤에 s 를 붙인다.
    void copy_string(const string &s); // str 에 s 를 복사한다.
    int strlen();                      // 문자열 길이 리턴
    void show();
};

string::string(char c, int n){
    str = new char[n+1];
    for (int i = 0; i < n; i++)
    {
        str[i] = c;
    }
    str[n]='\0';
    len=n;
    
}
string::string(const char* s){
    int i=0;
    while(s[i] != '\0'){
        i++;
    }
    str = new char[i];
    strcpy(str,s);
    len = i;
}
string::string(const string &s){
    len = s.len;
    str = new char[len+1];

    strcpy(str,s.str);

}
string::~string(){
    if(str) delete[] str;
}

void string::add_string(const string &s){
    char* tmp = str;
    str=new char[len+s.len+1];
    strcpy(str,tmp);
    strcpy(str+len,s.str);
    len+=s.len;
}
void string::copy_string(const string &s){
    len = s.len;
    str=new char[len+1];
    strcpy(str,s.str);
}
int string::strlen(){
    return len;
}
void string::show(){
    std::cout<<str<<std::endl;
}
int main(){
    string s1("hello");
    string s2= s1;
    string s4('a',10);
    s2.add_string(" world");
    s2.show();
    
    string s3("good");
    s3.copy_string(s2);
    s3.show();
    s4.show();

    std::cout<<s1.strlen()<<std::endl;
    std::cout<<s2.strlen()<<std::endl;
    std::cout<<s3.strlen()<<std::endl;
    std::cout<<s4.strlen()<<std::endl;
}