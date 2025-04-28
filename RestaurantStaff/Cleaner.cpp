#include "Cleaner.h"
#include <limits>

Cleaner::Cleaner(const string& name, int speed, int salary)
    : Staff(name), speed(speed), salary(salary) {
}

void Cleaner::show() const {
    cout << "Cleaner: " << name << ", Speed: " << speed << ", Salary: " << salary << endl;
}

void Cleaner::save(ostream& os) const {
    os << "Cleaner " << name << " " << speed << " " << salary << endl;
}

void Cleaner::modify() {
    cout << "Enter new Speed: ";
    if (!(cin >> speed)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Modification failed.\n"; return;
    }
    cout << "Enter new Salary: ";
    if (!(cin >> salary)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Modification failed.\n"; return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
