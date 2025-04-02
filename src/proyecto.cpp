#include<cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Contributor{
    string name;
    int age;
    int id;
    string description;
    int contribution_grade;
    Contributor* next;
    
    Contributor():name(""), age(0), id(0), description(""), contribution_grade(0), next(nullptr){}
    
    bool operator<(const Contributor& other)const{
        if(contribution_grade==other.contribution_grade){
            return age<other.age;
        }
        return contribution_grade>other.contribution_grade;
    }
};

struct ClanMember{
    int id;
    string name;
    string last_name;
    char gender;
    int age;
    int id_father;
    bool is_dead;
    bool was_chief;
    bool is_chief;
    Contributor*contributors;
    ClanMember*left;
    ClanMember*right;
    
    ClanMember():id(0), name(""), last_name(""), gender(' '), age(0), id_father(0),
                  is_dead(false), was_chief(false), is_chief(false),
                  contributors(nullptr), left(nullptr), right(nullptr){}
};

class ClanTree {
    private:
        ClanMember*root;
        ClanMember*createMemberFromCSV(const string& line);
        ClanMember*insertMember(ClanMember*node, ClanMember*newMember);
        ClanMember*findMemberById(ClanMember*node, int id)const;
        ClanMember*findMemberByName(ClanMember*node, const string& name, const string& last_name)const;
        ClanMember*findFather(ClanMember*node, int fatherId)const;
        ClanMember*findCurrentLeader(ClanMember*node)const;
        void clearTree(ClanMember*node);
        void printSuccession(ClanMember*node)const;
        void printMemberDetails(const ClanMember*member)const;
        void printContributors(const Contributor*contributor)const;
        void printAllMembers(ClanMember*node)const;
        ClanMember*findFirstLivingSon(ClanMember*parent)const;
        ClanMember*findFirstLivingMaleDescendant(ClanMember*ancestor)const;
        ClanMember*findFirstLivingFemaleDescendant(ClanMember*ancestor)const;
        ClanMember*findLivingSibling(ClanMember*node)const;
        ClanMember*findUncleOrAunt(ClanMember*node)const;
        ClanMember*findAncestorWithTwoChildren(ClanMember*node)const;
        void addContributorSorted(Contributor*& head, Contributor*newContributor);
        void clearContributors(Contributor*head);
        void updateChiefStatus(ClanMember*newLeader);
        
    public:
        ClanTree():root(nullptr){}
        ~ClanTree();
        
        void loadFromCSV(const string& filename);
        void loadContributors(const string& filename);
        void displaySuccessionLine() const;
        void updateLeadership();
        void editMember(int id);
        void printAllMembers() const;
        void printMember(int id) const;
        void printMember(const string& name, const string& last_name) const;
        void addContributor(int memberId, const string& name, int age, int id, 
                           const string& description, int grade);
    };
int main(){
    system("move proyecto.exe ..\\bin\\");
    return 0;
}