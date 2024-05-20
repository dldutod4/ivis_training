/*
new와 delete
heap 동적 메모리 할당.
new - 메모리 할당
delete - 메모리 해제 new로 할당한 공간만 해제가능


*/
// #include <iostream>

// int main(){
//     int arr_size=10;

//     int *list = new int[arr_size]; //배열도 할당가능
//     for (int i = 0; i < arr_size; i++)
//     {
//         std::cin >> list[i];
//     }
    
//     delete[] list;
//     std::cout << "해제" <<std::endl;

//     return 0;
// }

#include<iostream>
typedef struct Animal{
    int name;
    int age;
    int health;
    int food;
    int clean;
} Animal;
void newAnimal(Animal* p,int num){
    p = new Animal;
    p->name = num;
    p->age = 1;
    p->health=10;
}
void play(Animal& a){
    a.age++;
    a.health--;
}
void show_stat(Animal& a){
    std::cout 
    << a.name<<" " 
    << a.age <<" "
    << a.health <<std::endl;
}
int main(){
    Animal* list[30];
    int input;
    int num=0;
    while(1){
        std::cout <<"입력:"<<std::endl;
        std::cin>>input;
        if(input == 0){
            newAnimal(list[num],num);
            num++;
        }
        else if(input == 1){
            for (int i = 0; i < num; i++)
            {
                play(*list[num]);
            }

        }
        else if(input == 2){
            for (int i = 0; i < num; i++)
            {
                show_stat(*list[i]);
            }

        }
        else{
            break;
        }
    }
}