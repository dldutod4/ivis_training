#include "../include/family.h"

int main() {
    std::shared_ptr<Member> a = std::make_shared<Member>();
    std::shared_ptr<Member> b = std::make_shared<Member>();
    std::shared_ptr<Member> c = std::make_shared<Member>();
    std::shared_ptr<Member> d = std::make_shared<Member>();
    std::shared_ptr<Member> e = std::make_shared<Member>();
    FamilyTree ft;
    ft.AddMember(a);
    ft.AddMember(b);
    ft.AddMember(c);
    ft.AddMember(d);
    ft.AddMember(e);

    a->AddChild(b);
    a->AddChild(c);
    d->AddChild(e);
    a->AddSpouse(d);
}

/*

내 자식추가 a->b
자식 부모추가b->a
내 자식추가a->c
자식 부모추가c->a
내 자식추가d->e
자식 부모추가e->d
배우자 추가a->d
배우자 자식추가
내 자식추가
자식 부모추가
배우자 자식추가
자식 부모추가
자식 부모추가
배우자 자식추가
내 자식추가
자식 부모추가


*/