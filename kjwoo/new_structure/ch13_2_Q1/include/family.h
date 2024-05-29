#ifndef FAM_H
#define FAM_H
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>
class FamilyTree;
class Member : public std::enable_shared_from_this<Member> {
private:
    std::vector<std::shared_ptr<Member>> children;
    std::vector<std::weak_ptr<Member>> parents;
    std::vector<std::weak_ptr<Member>> spouse;

public:
    Member();
    ~Member();
    friend FamilyTree;
    void AddParent(const std::shared_ptr<Member>& parent);
    void AddSpouse(const std::shared_ptr<Member>& spouse);
    void AddChild(const std::shared_ptr<Member>& child);
};
class FamilyTree {
private:
    std::vector<std::shared_ptr<Member>> entire_family;
    std::set<std::shared_ptr<Member>> checked_member;

public:
    // 두 사람 사이의 촌수를 계산한다.
    int CalculateChon(Member* mem1, Member* mem2);
    void AddMember(std::shared_ptr<Member> mem);
};

#endif