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
        if (contribution_grade==other.contribution_grade){
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
    Contributor* contributors;
    ClanMember* left;
    ClanMember* right;

    ClanMember():id(0), name(""), last_name(""), gender(' '), age(0), id_father(0),
                  is_dead(false), was_chief(false), is_chief(false),
                  contributors(nullptr), left(nullptr), right(nullptr){}
};