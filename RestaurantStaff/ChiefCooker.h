#pragma once
#include "Cook.h"
#include <iostream>
#include <string>

class ChiefCooker : public Cook {
protected:
    string cuisine;
private:
    int dishesPerHour;
    int experience;
public:
    ChiefCooker(const string& name = "", const string& cuisine = "", int dishes = 0, int exp = 0);

    void show() const override;
    void save(ostream& os) const override;
    void modify() override;
};