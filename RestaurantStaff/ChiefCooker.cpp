#include "ChiefCooker.h"
#include <iostream>
#include <limits>

using namespace std;

ChiefCooker::ChiefCooker(const string& name, const string& cuisine, int dishes, int exp)
    : Cook(name), cuisine(cuisine), dishesPerHour(dishes), experience(exp) {
}

void ChiefCooker::show() const {
    cout << "ChiefCooker: " << getName()
        << ", Cuisine: " << cuisine
        << ", Dishes/hour: " << dishesPerHour
        << ", Experience: " << experience << endl;
}

void ChiefCooker::save(ostream& os) const {
    os << "ChiefCooker " << getName() << " " << cuisine << " "
        << dishesPerHour << " " << experience << endl;
}

void ChiefCooker::modify() {
    cout << "Enter new Cuisine: ";
    getline(cin, cuisine);

    cout << "Enter new Dishes/hour: ";
    if (!(cin >> dishesPerHour)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Modification failed.\n"; return;
    }

    cout << "Enter new Experience: ";
    if (!(cin >> experience)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Modification failed.\n"; return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
