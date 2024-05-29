#include "../include/family.h"

int main() {
    std::shared_ptr<Member> a = std::make_shared<Member>();
    std::shared_ptr<Member> b = std::make_shared<Member>();
    std::shared_ptr<Member> c = std::make_shared<Member>();
    std::shared_ptr<Member> d = std::make_shared<Member>();
    std::shared_ptr<Member> e = std::make_shared<Member>();
    std::shared_ptr<Member> f = std::make_shared<Member>();
    FamilyTree ft;
    ft.AddMember(a);
    ft.AddMember(b);
    ft.AddMember(c);
    ft.AddMember(d);
    ft.AddMember(e);
    ft.AddMember(f);

    a->AddChild(b);
    a->AddChild(c);
    d->AddChild(e);
    c->AddChild(f);
    a->AddSpouse(d);  // 배우자를 추가하면 배우자쪽 자식이 내자식으로 들어오고, 내자식이 배우자 자식으로 들어간다.
                      // 자식들도 부모가 추가된다.
    /*
    가계도
                            (a     -    d)
                         /       \         \
                        b        c           e
                                    \
                                     f

    */
    std::cout << "d-f chon : " << ft.CalculateChon(d.get(), f.get()) << std::endl;
}

/*



*/