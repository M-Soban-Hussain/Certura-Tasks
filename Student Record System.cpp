#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

// lol student info class
class Person {
public:
    int rNo;
    char fullName[50];
    float markz;

    void get() {
        cout << "roll no?? : ";  cin >> rNo;
        cout << "Name plz : "; cin.ignore();  cin.getline(fullName, 50);
        cout << "Marks : "; cin >> markz;
    }

    void out() const {
        cout << "Roll : " << rNo << "\nName: " << fullName << "\nMarks: " << markz << endl;
    }

    int fetchRoll() const {
        return rNo;
    }
};

void addOne() {
    Person p;
    p.get();

    ofstream f("students.dat", ios::binary | ios::app);
    f.write((char*)&p, sizeof(p));
    f.close();

    cout << "added...\n";
}

// display all junk
void readAll() {
    Person tmp;
    ifstream f("students.dat", ios::binary);

    while (f.read((char*)&tmp, sizeof(tmp))) {
        tmp.out();
        cout << "---x---\n";
    }
    f.close();
}

// delete a person by roll
void zap() {
    int rid;
    cout << "roll no to delete: "; cin >> rid;

    ifstream a("students.dat", ios::binary);
    ofstream b("temp.dat", ios::binary);

    Person t; bool ok = 0;
    while (a.read((char*)&t, sizeof(t))) {
        if (t.fetchRoll() == rid) {
            ok = 1;
            continue;
        }
        b.write((char*)&t, sizeof(t));
    }

    a.close();   b.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (ok)cout << "deleted.\n"; else cout << "not found\n";
}

// main with messy layout
int main() {
    int userOption;
    do {

        cout << "\n5. Exit\n";
        cout << "1. Insert Student\n";
        cout << "4. Delete Entry\n";
        cout << "2. Display All\n";
        cout << "ur option -> ";
        cin >> userOption;

        switch (userOption) {
        case 1: addOne(); break;
        case 2:readAll(); break;
        case 4: zap(); break;
        case 5: cout << "bye\n"; break;
        default: cout << "try again\n";
        }
    } while (userOption != 5);

    return 0;
}
