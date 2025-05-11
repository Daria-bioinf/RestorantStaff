#include "Sushef.h"
#include <limits>

Sushef::Sushef(const string& name, const string& language, int orders, int acc)
    : ChiefCooker(name), language(language), specialOrders(orders), accuracy(acc) {
}

void Sushef::show() const {
    cout << "Sushef: " << name << ", Language: " << language
        << ", Special Orders: " << specialOrders << ", Accuracy: " << accuracy << endl;
}

void Sushef::save(ostream& os) const {
    os << "Sushef " << name << " " << language << " "
        << specialOrders << " " << accuracy << endl;
}

void Sushef::modify() {
    cout << "Enter new Language: ";
    if (!(cin >> language)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Modification failed.\n"; return;
    }
    cout << "Enter new Special Orders: ";
    if (!(cin >> specialOrders)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Modification failed.\n"; return;
    }
    cout << "Enter new Accuracy: ";
    if (!(cin >> accuracy)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Modification failed.\n"; return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
