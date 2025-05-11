#pragma once
#include "Cook.h"
#include <string>
#include <iostream>

class ChiefCooker : public Cook {
protected:
    std::string cuisine;
private:
    int dishesPerHour;
    int experience;
public:
    ChiefCooker(const std::string& name = "", const std::string& cuisine = "", int dishes = 0, int exp = 0);

    void show() const override;
    void save(std::ostream& os) const override;
    void modify() override;
};
