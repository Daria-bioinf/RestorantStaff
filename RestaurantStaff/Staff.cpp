#include "Staff.h"

Staff::Staff(const string& name) : name(name) {}

Staff::~Staff() {}

string Staff::getName() const {
    return name;
}

void Staff::setName(const string& newName) {
    name = newName;
}
