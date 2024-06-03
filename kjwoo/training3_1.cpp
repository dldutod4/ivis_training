#include<iostream>
typedef struct Animal{
    int name;
    int age;
    int health;
    int food;
    int clean;
} Animal;
void newAnimal(Animal& a,int num){
    a.name = num;
    a.age = 1;
    a.health=10;
}
void play(Animal& a){
    a.age+=1;
    a.health-=1;
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
            list[num] = new Animal;
            newAnimal(*list[num],num);
            num++;
        }
        else if(input == 1){
            for (int i = 0; i < num; i++)
            {
                play(*list[i]);
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