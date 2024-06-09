#include <iostream>
#include <memory>
#include <vector>

class Member {
private:
    std::vector<std::shared_ptr<Member>> children;
    std::vector<std::weak_ptr<Member>> parents;
    std::vector<std::weak_ptr<Member>> spouses;

public:
    void AddParent(const std::shared_ptr<Member>& parent) { parents.push_back(parent); }
    void AddSpouse(const std::shared_ptr<Member>& spouse) { spouses.push_back(spouse); }
    void AddChild(const std::shared_ptr<Member>& child) {
        child->AddParent(std::shared_ptr<Member>(this));
        children.push_back(child);
    }
};

class FamilyTree {
public:
    std::vector<std::shared_ptr<Member>> entire_family;

    // 두 사람 사이의 촌수를 계산한다.
    int CalculateChon(Member* mem1, Member* mem2);
};

int main() {
    FamilyTree Family;
    std::shared_ptr<Member> GrandPa = std::make_shared<Member>();
    std::shared_ptr<Member> GrandMa = std::make_shared<Member>();
    std::shared_ptr<Member> Pa = std::make_shared<Member>();
    std::shared_ptr<Member> Ma = std::make_shared<Member>();
    std::shared_ptr<Member> Bro = std::make_shared<Member>();
    std::shared_ptr<Member> Me = std::make_shared<Member>();

    Family.entire_family.push_back(GrandPa);
    Family.entire_family.push_back(GrandMa);
    Family.entire_family.push_back(Pa);
    Family.entire_family.push_back(Ma);
    Family.entire_family.push_back(Bro);
    Family.entire_family.push_back(Me);
}