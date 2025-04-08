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
    
    ClanMember*insertMember(ClanMember*node, ClanMember*newMember){
        if(!node) return newMember;

        if(newMember->id<node->id){
            node->left=insertMember(node->left, newMember);
        } else if (newMember->id>node->id) {
            node->right=insertMember(node->right, newMember);
        } else{
            delete newMember;
            return node;
        }
        return node;
    }

    ClanMember*findMemberById(ClanMember*node, int id)const{
        if (!node) return nullptr;
        if (id<node->id)return findMemberById(node->left, id);
        if (id>node->id)return findMemberById(node->right, id);
        return node;
    }

    ClanMember*findMemberByName(ClanMember* node, const string& name, const string& last_name) const {
        if(!node)return nullptr;
        if(node->name==name&&node->last_name==last_name) return node;

        ClanMember*found=findMemberByName(node->left, name, last_name);
        if (found)return found;
        return findMemberByName(node->right, name, last_name);
    }

    ClanMember*findFather(ClanMember*node, int fatherId)const{
        if(!node)return nullptr;
        if(node->id==fatherId)return node;

        ClanMember*found=findFather(node->left, fatherId);
        if(found)return found;
        return findFather(node->right, fatherId);
    }

    ClanMember*findCurrentLeader(ClanMember* node) const {
        if(!node) return nullptr;
        if(node->is_chief&&!node->is_dead)return node;

        ClanMember*found=findCurrentLeader(node->left);
        if(found)return found;
        return findCurrentLeader(node->right);
    }

    void clearTree(ClanMember*node){
        if(node){
            clearTree(node->left);
            clearTree(node->right);
            clearContributors(node->contributors);
            delete node;
        }
    }

    void printSuccession(ClanMember*node)const{
        if(!node)return;
        printSuccession(node->left);

        if(!node->is_dead&&(node->is_chief||node->was_chief)){
            cout<<"ID: "<<node->id<<", Nombre: "<<node->name<< " "<<node->last_name;
            if(node->is_chief)cout<<" LIDER ACTUAL";
            cout<<endl;
        }

        printSuccession(node->right);
    }
    
    void printMemberDetails(const ClanMember* member) const {
        if (!member) return;
        cout<<"\nID: "<<member->id<<endl;
        cout<<"Nombre: "<<member->name<<" "<<member->last_name<<endl;
        cout<<"Genero: "<<member->gender<<endl;
        cout<<"Edad: "<<member->age<<endl;
        cout<<"ID Padre: "<<member->id_father<<endl;
        cout<<"Estado: "<<(member->is_dead ?"Muerto":"Vivo")<<endl;
        cout<<"Fue jefe: "<<(member->was_chief?"Si":"No")<<endl;
        cout<<"Es jefe actual: "<<(member->is_chief ?"Si":"No")<<endl;

        if (member->contributors){
            cout<<"\nContribuidores:\n";
            printContributors(member->contributors);
        }
    }

    void printContributors(const Contributor* contributor) const {
        while (contributor) {
            cout<<" - " << contributor->name<<" (Edad: "<<contributor->age<< ", ID: "<<contributor->id<<")\n";
            cout<<"   Descripcion: "<<contributor->description<<endl;
            cout<<"   Grado de contribucion: "<<contributor->contribution_grade<<"/10\n\n";
            contributor=contributor->next;
        }
    }

    void printAllMembers(ClanMember*node)const{
        if(!node)return;
        printAllMembers(node->left);
        printMemberDetails(node);
        printAllMembers(node->right);
    }