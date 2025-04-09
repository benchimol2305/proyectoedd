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

    ClanMember*findFirstLivingSon(ClanMember*parent)const{
        if(!parent)return nullptr;
        ClanMember*current=root;
        while(current){
            if(current->id_father==parent->id&&!current->is_dead){
                if(current->gender=='H')return current;
            }
            if(parent->id<current->id)current=current->left;
            else current=current->right;
        }
        return nullptr;
    }

    ClanMember*findFirstLivingMaleDescendant(ClanMember*ancestor) const{
        if(!ancestor)return nullptr;
        ClanMember*son=findFirstLivingSon(ancestor);
        if(son)return son;

        ClanMember*current=root;
        while (current){
            if (current->id_father==ancestor->id&&!current->is_dead&&current->gender=='M'){
                ClanMember*grandson=findFirstLivingMaleDescendant(current);
                if(grandson)return grandson;
            }
            if (ancestor->id<current->id)current=current->left;
            else current=current->right;
        }
        return nullptr;
    }

    ClanMember*findFirstLivingFemaleDescendant(ClanMember*ancestor)const{
        if(!ancestor)return nullptr;
        ClanMember*current=root;
        while(current){
            if(current->id_father==ancestor->id&&!current->is_dead){
                if(current->gender=='M'){
                    ClanMember*femaleDescendant=findFirstLivingFemaleDescendant(current);
                    if(femaleDescendant)return femaleDescendant;
                }else{
                    return current;
                }
            }
            if(ancestor->id< current->id)current=current->left;
            else current=current->right;
        }
        return nullptr;
    }

    ClanMember*findLivingSibling(ClanMember*node)const{
        if(!node||node->id_father==0)return nullptr;
        ClanMember*father=findMemberById(root, node->id_father);
        if(!father)return nullptr;

        ClanMember*current=root;
        while(current){
            if(current->id_father==father->id&&current->id!=node->id&&!current->is_dead){
                return current;
            }
            if(father->id<current->id)current=current->left;
            else current=current->right;
        }
        return nullptr;
    }

    ClanMember*findUncleOrAunt(ClanMember*node)const{
        if(!node||node->id_father==0)return nullptr;
        ClanMember*father=findMemberById(root, node->id_father);
        if(!father||father->id_father==0)return nullptr;
        ClanMember*grandparent=findMemberById(root, father->id_father);
        if(!grandparent)return nullptr;

        ClanMember*current=root;
        while(current){
            if(current->id_father==grandparent->id&&current->id!=father->id&&!current->is_dead){
                return current;
            }
            if(grandparent->id<current->id)current=current->left;
            else current=current->right;
        }
        return nullptr;
    }

    ClanMember*findAncestorWithTwoChildren(ClanMember* node)const{
        if(!node)return nullptr;
        ClanMember*ancestor=findMemberById(root, node->id_father);
        while(ancestor){
            int childCount=0;
            ClanMember*current=root;
            while(current){
                if(current->id_father==ancestor->id&&!current->is_dead){
                    childCount++;
                    if(childCount>=2)return ancestor;
                }
                if(ancestor->id<current->id)current=current->left;
                else current=current->right;
            }
            ancestor=findMemberById(root,ancestor->id_father);
        }
        return nullptr;
    }

    void addContributorSorted(Contributor*& head, Contributor*newContributor){
        if (!head||*newContributor<*head){
            newContributor->next=head;
            head=newContributor;
        } else{
            Contributor*curr=head;
            while(curr->next&&!(*newContributor<*curr->next)){
                curr=curr->next;
            }
            newContributor->next=curr->next;
            curr->next=newContributor;
        }
    }

    void clearContributors(Contributor* head) {
        while (head) {
            Contributor* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void updateChiefStatus(ClanMember*newLeader){
        if (!newLeader)return;
        ClanMember*current=root;
        while(current){
            if(current->is_chief){
                current->is_chief=false;
                current->was_chief=true;
                break;
            }
            if(newLeader->id<current->id)current=current->left;
            else current=current->right;
        }
        newLeader->is_chief=true;
        newLeader->was_chief=true;
    }

    void saveMembersToCSVHelper(ClanMember* node, ofstream& file) const {
        if (!node) return;
        saveMembersToCSVHelper(node->left, file);
        file << node->id << "," << node->name << "," << node->last_name << ","
             << node->gender << "," << node->age << "," << node->id_father << ","
             << (node->is_dead ? "1" : "0") << ","
             << (node->was_chief ? "1" : "0") << ","
             << (node->is_chief ? "1" : "0") << "\n";
        saveMembersToCSVHelper(node->right, file);
    }

    void saveMembersToCSV() const {
        ofstream file(membersFilename);
        if (!file.is_open()) {
            cerr << "Error al abrir el archivo: " << membersFilename << endl;
            return;
        }
        file << "id,name,last_name,gender,age,id_father,is_dead,was_chief,is_chief\n";
        saveMembersToCSVHelper(root, file);
        file.close();
    }

    void saveContributorsToCSVHelper(ClanMember* node, ofstream& file) const {
        if (!node) return;
        saveContributorsToCSVHelper(node->left, file);
        Contributor* contributor = node->contributors;
        while (contributor) {
            file << node->id << "," << contributor->name << "," << contributor->age << ","
                 << contributor->id << "," << contributor->description << ","
                 << contributor->contribution_grade << "\n";
            contributor = contributor->next;
        }
        saveContributorsToCSVHelper(node->right, file);
    }

    void saveContributorsToCSV() const {
        ofstream file(contributorsFilename);
        if (!file.is_open()) {
            cerr << "Error al abrir el archivo: " << contributorsFilename << endl;
            return;
        }
        file << "id_miembro,nombre,edad,id,descripcion,grado\n";
        saveContributorsToCSVHelper(root, file);
        file.close();
    }

       
    void printAllContributorsHelper(ClanMember* node) const {
        if (!node) return;
        printAllContributorsHelper(node->left);
        if (node->contributors) {
            cout << "\nContribuidores de " << node->name << " " << node->last_name << " (ID: " << node->id << "):\n";
            printContributors(node->contributors);
        }
        printAllContributorsHelper(node->right);
    }

    void searchContributorHelper(ClanMember* node, const string& name) const {
        if (!node) return;
        searchContributorHelper(node->left, name);
        Contributor* contributor = node->contributors;
        while (contributor) {
            if (contributor->name.find(name) != string::npos) {
                cout << "\nContribuidor encontrado:\n";
                cout << "Nombre: " << contributor->name << "\n";
                cout << "Edad: " << contributor->age << "\n";
                cout << "ID: " << contributor->id << "\n";
                cout << "Descripcion: " << contributor->description << "\n";
                cout << "Grado: " << contributor->contribution_grade << "\n";
                cout << "Pertenece a: " << node->name << " " << node->last_name << " (ID: " << node->id << ")\n";
            }
            contributor = contributor->next;
        }
        searchContributorHelper(node->right, name);
    }

 public:
    ClanTree() : root(nullptr), membersFilename("Clan.csv"), contributorsFilename("contribuidores.csv") {}
    ~ClanTree() { clearTree(root); }

    void loadFromCSV(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error al abrir el archivo: " << filename << endl;
            return;
        }
        string line;
        getline(file, line); // Saltar cabecera
        while (getline(file, line)) {
            ClanMember* newMember = createMemberFromCSV(line);
            root = insertMember(root, newMember);
        }
        file.close();
    }

    void loadContributors(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error al abrir el archivo: " << filename << endl;
            return;
        }
        string line;
    getline(file, line); // Saltar cabecera
    while (getline(file, line)) {
        size_t pos = 0;
        size_t start = 0;
        int field = 0;
        int memberId = 0;
        Contributor* newContributor = new Contributor();
        while ((pos = line.find(',', start)) != string::npos || start < line.size()) {
            string token;
            if (pos != string::npos) {
                token = line.substr(start, pos - start);
                start = pos + 1;
            } else {
                token = line.substr(start); // ultimo campo
                start = line.size();
            }
            switch (field) {
                case 0: 
                    memberId = stoi(token);
                    break;
                case 1: 
                    newContributor->name = token;
                    break;
                case 2: 
                    newContributor->age = stoi(token);
                    break;
                case 3: 
                    newContributor->id = stoi(token);
                    break;
                case 4: 
                    newContributor->description = token;
                    break;
                case 5: 
                    newContributor->contribution_grade = stoi(token); // Leer directamente el valor del grado
                    break;
                default:
                    break;
            }
            field++;
        }

        ClanMember* member = findMemberById(root, memberId);
        if (member) {
            addContributorSorted(member->contributors, newContributor);
        } else {
            delete newContributor; // Si no hay miembro, liberar memoria
        }
    }
    file.close();
}

void displaySuccessionLine() const {
    cout << "\nLinea de Sucesion Actual:\n";
    printSuccession(root);
}

void updateLeadership() {
ClanMember* currentLeader = findCurrentLeader(root);

// Verificar si existe un lider actual
if (currentLeader) {
    // Comprobar si el lider actual esta muerto o supera la edad limite
    if (currentLeader->is_dead || currentLeader->age > 70) {
        cout << "\nEl lider actual ya no cumple con las condiciones para liderar.\n";

        // Buscar un nuevo lider segun las reglas
        ClanMember* newLeader = findFirstLivingMaleDescendant(currentLeader);
        if (!newLeader) newLeader = findFirstLivingFemaleDescendant(currentLeader);
        if (!newLeader) newLeader = findLivingSibling(currentLeader);
        if (!newLeader) newLeader = findUncleOrAunt(currentLeader);
        if (!newLeader) {
            ClanMember* ancestor = findAncestorWithTwoChildren(currentLeader);
            if (ancestor) {
                newLeader = findFirstLivingMaleDescendant(ancestor);
                if (!newLeader) newLeader = findFirstLivingFemaleDescendant(ancestor);
            }
        }

         // Si se encuentra un nuevo lider
         if (newLeader) {
            // Actualizar los estados del lider actual y el nuevo lider
            currentLeader->is_chief = false;
            currentLeader->was_chief = true;

            newLeader->is_chief = true;

            cout << "\nEl nuevo lider es: " << newLeader->name << " " << newLeader->last_name
                 << " (ID: " << newLeader->id << ")\n";

            // Guardar los cambios en el CSV
            saveMembersToCSV();
        } else {
            cout << "\nNo se pudo encontrar un sucesor adecuado.\n";
        }
    } else {
        cout << "\nEl lider actual sigue siendo: " << currentLeader->name << " "
             << currentLeader->last_name << " (ID: " << currentLeader->id << ")\n";
    }
} else {
    cout << "\nNo hay un lider actual en el clan.\n";
}
}

void editMember(int id) {
    ClanMember* member = findMemberById(root, id);
    if (!member) {
        cout << "Miembro no encontrado con ID: " << id << endl;
        return;
    }
    cout << "\nEditando miembro: " << member->name << " " << member->last_name << endl;
    cout << "1. Nombre\n2. Apellido\n3. Genero\n4. Edad\n5. Estado (vivo/muerto)\n";
    cout << "Seleccione campo a editar: ";
    int choice;
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1: getline(cin, member->name); break;
        case 2: getline(cin, member->last_name); break;
        case 3: cin >> member->gender; break;
        case 4: cin >> member->age; break;
        case 5: {
            cin >> member->is_dead;
            if (!member->is_dead && member->was_chief) member->was_chief = false;
            break;
        }
        default: cout << "Opcion no valida.\n";
    }
    saveMembersToCSV();
    cout << "Miembro actualizado con exito.\n";
}
void printAllMembers() const {
    cout << "\nTodos los miembros del clan:\n";
    printAllMembers(root);
}

void printMember(int id) const {
    ClanMember* member = findMemberById(root, id);
    if (member) printMemberDetails(member);
    else cout << "Miembro no encontrado con ID: " << id << endl;
}

void printMember(const string& name, const string& last_name) const {
    ClanMember* member = findMemberByName(root, name, last_name);
    if (member) printMemberDetails(member);
    else cout << "Miembro no encontrado: " << name << " " << last_name << endl;
}

void addContributor(int memberId, const string& name, int age, int id,
    const string& description, int grade) {
ClanMember* member = findMemberById(root, memberId);
if (!member) {
cout << "Miembro no encontrado con ID: " << memberId << endl;
return;
}
Contributor* newContributor = new Contributor();
newContributor->name = name;
newContributor->age = age;
newContributor->id = id;
newContributor->description = description;
newContributor->contribution_grade = grade;
addContributorSorted(member->contributors, newContributor);
saveContributorsToCSV();
cout << "Contribuidor agregado con exito.\n";
}

void printAllContributors() const {
cout << "\n=== Todos los contribuidores del clan ===\n";
printAllContributorsHelper(root);
}

void searchContributor(const string& name) const {
cout << "\n=== Resultados de busqueda para \"" << name << "\" ===\n";
searchContributorHelper(root, name);
}
void editContributor(int memberId, int contributorId) {
    ClanMember* member = findMemberById(root, memberId);
    if (!member) {
        cout << "Miembro no encontrado con ID: " << memberId << endl;
        return;
    }
    Contributor* contributor = member->contributors;
    Contributor* prev = nullptr;
    bool found = false;
    while (contributor) {
        if (contributor->id == contributorId) {
            found = true;
            break;
        }
        prev = contributor;
        contributor = contributor->next;
    }
    if (!found) {
        cout << "Contribuidor no encontrado con ID: " << contributorId << endl;
        return;
    }
    cout << "\nEditando contribuidor: " << contributor->name << " (ID: " << contributor->id << ")\n";
    cout << "1. Nombre\n2. Edad\n3. Descripcion\n4. Grado de contribucion\n";
    cout << "Seleccione campo a editar: ";
    int choice;
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1: getline(cin, contributor->name); break;
        case 2: cin >> contributor->age; break;
        case 3: getline(cin, contributor->description); break;
        case 4: cin >> contributor->contribution_grade; break;
        default: cout << "Opcion no valida.\n";
    }




















        




