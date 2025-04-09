#include<iostream>
#include "../src/proyecto.h"
#include<fstream>
using namespace std;

int main() {
    ClanTree clan;
    clan.loadFromCSV("../bin/Clan.csv");
    clan.loadContributors("../bin/contribuidores.csv");

 int option;
    do {
        cout << "\n=== Sistema de Gestion del Clan ===\n";
        cout << "1. Mostrar linea de sucesion\n";
        cout << "2. Actualizar liderazgo\n";
        cout << "3. Mostrar todos los miembros\n";
        cout << "4. Buscar miembro por ID\n";
        cout << "5. Buscar miembro por nombre\n";
        cout << "6. Editar miembro\n";
        cout << "7. Agregar contribuidor\n";
        cout << "8. Mostrar todos los contribuidores\n";
        cout << "9. Buscar contribuidor por nombre\n";
        cout << "10. Editar contribuidor\n";
        cout << "11. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> option;
        cin.ignore();

      switch (option) {
            case 1: clan.displaySuccessionLine(); break;
            case 2: clan.updateLeadership(); break;
            case 3: clan.printAllMembers(); break;
            case 4: {
                int id; cout << "Ingrese ID del miembro: "; cin >> id;
                clan.printMember(id); break;
            }
           case 5: {
                string name, last_name;
                cout << "Ingrese nombre: "; getline(cin, name);
                cout << "Ingrese apellido: "; getline(cin, last_name);
                clan.printMember(name, last_name); break;
            }
            case 6: {
                int id; cout << "Ingrese ID del miembro a editar: "; cin >> id;
                clan.editMember(id); break;
            }
            case 7: {
                int memberId, age, id, grade;
                string name, description;
                cout << "ID del miembro: "; cin >> memberId; cin.ignore();
                cout << "Nombre del contribuidor: "; getline(cin, name);
                cout << "Edad: "; cin >> age; cin.ignore();
                cout << "ID del contribuidor: "; cin >> id; cin.ignore();
                cout << "Descripcion: "; getline(cin, description);
                cout << "Grado (1-10): "; cin >> grade; cin.ignore();
                clan.addContributor(memberId, name, age, id, description, grade);
                break;
            }
            case 8: clan.printAllContributors(); break;
            case 9: {
                string name; cout << "Ingrese nombre: "; getline(cin, name);
                clan.searchContributor(name); break;
            }
            case 10: {
                int memberId, contributorId;
                cout << "ID del miembro: "; cin >> memberId;
                cout << "ID del contribuidor: "; cin >> contributorId;
                clan.editContributor(memberId, contributorId); break;
            }
            case 11: cout << "Saliendo...\n"; break;
            default: cout << "Opcion no valida.\n";
        }
    } while (option != 11);

    return 0;
}