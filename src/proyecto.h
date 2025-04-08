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

class ClanTree{
    private:
        ClanMember*root;
        string membersFilename;
        string contributorsFilename;
    
        ClanMember*createMemberFromCSV(const string& line){
        ClanMember*newMember=new ClanMember();
        size_t pos=0;
        size_t start=0;
        int field=0;
    
        while ((pos = line.find(',', start))!=string::npos||start<line.size()){
            string token;
            if (pos!=string::npos){
                token=line.substr(start, pos - start);
                start=pos+1;
            } else {
                token=line.substr(start); 
                start=line.size();
            }
    
            switch (field){
                case 0: 
                    newMember->id=stoi(token);
                    break;
                case 1: 
                    newMember->name=token;
                    break;
                case 2: 
                    newMember->last_name=token;
                    break;
                case 3: 
                    newMember->gender=token[0];
                    break;
                case 4: 
                    newMember->age=stoi(token);
                    break;
                case 5: 
                    newMember->id_father=stoi(token);
                    break;
                case 6: 
                    newMember->is_dead=(token=="1"); 
                    break;
                case 7: 
                    newMember->was_chief=(token=="1"); 
                    break;
                case 8: 
                    newMember->is_chief=(token=="1");
                    break;
                default:
                    break;
            }
            field++;
        }
        return newMember;
    }