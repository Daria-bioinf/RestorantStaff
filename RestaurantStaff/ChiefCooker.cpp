#include "ChiefCooker.h"
#include <limits>

ChiefCooker::ChiefCooker(const string& name, const string& cuisine, int dishes, int exp)
    : Staff(name), cuisine(cuisine), dishesPerHour(dishes), experience(exp) {
}

void ChiefCooker::show() const {
    cout << "ChiefCooker: " << name << ", Cuisine: " << cuisine
        << ", Dishes/hour: " << dishesPerHour << ", Experience: " << experience << endl;
}

void ChiefCooker::save(ostream& os) const {
    os << "ChiefCooker " << name << " " << cuisine << " "
        << dishesPerHour << " " << experience << endl;
}

void ChiefCooker::modify() {
    cout << "Enter new Cuisine (num): ";
    if (!(cin >> cuisine)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Modification failed.\n"; return;
    }
    cout << "Enter new Dishes/hour (num):";
    if (!(cin >> dishesPerHour)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Modification failed.\n"; return;
    }
    cout << "Enter new Experience (num):";
    if (!(cin >> experience)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Modification failed.\n"; return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
