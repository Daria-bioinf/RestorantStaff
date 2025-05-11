#include "PastyCook.h"
#include <limits>

PastyCook::PastyCook(const string& name, const string& cuisine, int cakes, int skill)
    : Cook (name), cuisine(cuisine), cakesPerDay(cakes), skill(skill) {
}

void PastyCook::show() const {
    cout << "PastyCook: " << name << ", Cuisine: " << cuisine
        << ", Cakes/day: " << cakesPerDay << ", Skill: " << skill << endl;
}

void PastyCook::save(ostream& os) const {
    os << "PastyCook " << name << " " << cuisine << " "
        << cakesPerDay << " " << skill << endl;
}

void PastyCook::modify() {
    cout << "Enter new Cuisine: ";
    if (!(cin >> cuisine)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Modification failed.\n"; return;
    }
    cout << "Enter new Cakes/day: ";
    if (!(cin >> cakesPerDay)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Modification failed.\n"; return;
    }
    cout << "Enter new Skill: ";
    if (!(cin >> skill)) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Modification failed.\n"; return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
