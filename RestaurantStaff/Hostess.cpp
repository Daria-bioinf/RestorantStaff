// Hostess.cpp
#include "Hostess.h"
#include <limits>

Hostess::Hostess(const string& name, const string& language, int tables, int greet, int friendly)
    : Staff(name), language(language), tables(tables), greetingScore(greet), friendliness(friendly) {
}

void Hostess::show() const {
    cout << "Hostess: " << name << ", Language: " << language
        << ", Tables: " << tables << ", Greeting: " << greetingScore
        << ", Friendliness: " << friendliness << endl;
}

void Hostess::save(ostream& os) const {
    os << "Hostess " << name << " " << language << " "
        << tables << " " << greetingScore << " " << friendliness << endl;
}

void Hostess::modify() {
    cout << "Enter new Language: ";
    if (!(cin >> language)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Modification failed.\n"; return;
    }
    cout << "Enter new Tables: ";
    if (!(cin >> tables)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Modification failed.\n"; return;
    }
    cout << "Enter new Greeting Score: ";
    if (!(cin >> greetingScore)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Modification failed.\n"; return;
    }
    cout << "Enter new Friendliness: ";
    if (!(cin >> friendliness)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Modification failed.\n"; return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
