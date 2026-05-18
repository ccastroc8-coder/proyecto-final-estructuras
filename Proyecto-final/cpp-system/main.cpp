#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// ==========================
// ESTRUCTURA STUDENT
// ==========================

struct Student {

    int student_id;
    string full_name;
    string career;
    int semester;
    float gpa;
    int skill_score;

};

// ==========================
// NODO PARA LISTA ENLAZADA
// ==========================

struct Node {

    Student data;
    Node* next;

};

// ==========================
// HASH TABLE
// ==========================

class HashTable {

private:

    static const int SIZE = 10;

    Node* table[SIZE];

    int totalStudents;
    int collisions;

public:

    HashTable() {

        totalStudents = 0;
        collisions = 0;

        for(int i = 0; i < SIZE; i++) {
            table[i] = NULL;
        }
    }

    int hashFunction(int id) {
        return id % SIZE;
    }

    void insert(Student student) {

        int index = hashFunction(student.student_id);

        Node* temp = table[index];

        while(temp != NULL) {

            if(temp->data.student_id == student.student_id) {

                cout << "\nERROR: ID duplicado\n";
                return;
            }

            temp = temp->next;
        }

        Node* newNode = new Node();

        newNode->data = student;
        newNode->next = NULL;

        if(table[index] != NULL) {

            collisions++;
            newNode->next = table[index];
        }

        table[index] = newNode;

        totalStudents++;
    }

    void search(int id) {

        int index = hashFunction(id);

        Node* temp = table[index];

        while(temp != NULL) {

            if(temp->data.student_id == id) {

                cout << "\n===== ESTUDIANTE =====\n";

                cout << "ID: "
                     << temp->data.student_id << endl;

                cout << "Nombre: "
                     << temp->data.full_name << endl;

                cout << "Carrera: "
                     << temp->data.career << endl;

                cout << "Semestre: "
                     << temp->data.semester << endl;

                cout << "GPA: "
                     << temp->data.gpa << endl;

                cout << "Skill Score: "
                     << temp->data.skill_score << endl;

                return;
            }

            temp = temp->next;
        }

        cout << "\nEstudiante no encontrado\n";
    }

    void display() {

        cout << "\n===== TABLA HASH =====\n";

        for(int i = 0; i < SIZE; i++) {

            cout << "\nBucket " << i << ": ";

            Node* temp = table[i];

            while(temp != NULL) {

                cout << "[" 
                     << temp->data.student_id
                     << " - "
                     << temp->data.full_name
                     << "] -> ";

                temp = temp->next;
            }

            cout << "NULL";
        }

        cout << endl;
    }

    void statistics() {

        float loadFactor =
        (float) totalStudents / SIZE;

        cout << "\n===== ESTADISTICAS =====\n";

        cout << "Total estudiantes: "
             << totalStudents << endl;

        cout << "Colisiones: "
             << collisions << endl;

        cout << "Factor de carga: "
             << loadFactor << endl;
    }

};

// ==========================
// CARGAR CSV
// ==========================

void loadCSV(string filename,
             HashTable& hashTable) {

    ifstream file(filename);

    if(!file.is_open()) {

        cout << "\nError al abrir CSV\n";
        return;
    }

    string line;

    getline(file, line);

    while(getline(file, line)) {

        stringstream ss(line);

        Student s;

        string temp;

        getline(ss, temp, ',');
        s.student_id = stoi(temp);

        getline(ss, s.full_name, ',');

        getline(ss, s.career, ',');

        getline(ss, temp, ',');
        s.semester = stoi(temp);

        getline(ss, temp, ',');
        s.gpa = stof(temp);

        getline(ss, temp, ',');
        s.skill_score = stoi(temp);

        hashTable.insert(s);
    }

    file.close();

    cout << "\nCSV cargado correctamente\n";
}

// ==========================
// MENU
// ==========================

void menu() {

    cout << "\n===== RED SOCIAL ACADEMICA =====\n";

    cout << "1. Cargar estudiantes CSV\n";
    cout << "2. Mostrar Tabla Hash\n";
    cout << "3. Buscar estudiante\n";
    cout << "4. Mostrar estadisticas\n";
    cout << "5. Salir\n";

    cout << "Seleccione opcion: ";
}

// ==========================
// MAIN
// ==========================

int main() {

    HashTable hashTable;

    int option;

    do {

        menu();

        cin >> option;

        switch(option) {

            case 1:

                loadCSV("../dataset/estudiantes.csv",
                        hashTable);

                break;

            case 2:

                hashTable.display();

                break;

            case 3: {

                int id;

                cout << "\nIngrese ID: ";
                cin >> id;

                hashTable.search(id);

                break;
            }

            case 4:

                hashTable.statistics();

                break;

            case 5:

                cout << "\nSaliendo...\n";

                break;

            default:

                cout << "\nOpcion invalida\n";
        }

    } while(option != 5);

    return 0;
}