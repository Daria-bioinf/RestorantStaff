#pragma once
#include "ChiefCooker.h"
#include <iostream>
#include <string>

class Sushef : public ChiefCooker {
protected:
    string language;
private:
    int specialOrders;
    int accuracy;
public:
    Sushef(const string& name = "", const string& language = "", int orders = 0, int acc = 0);

    void show() const override;
    void save(ostream& os) const override;
    void modify() override;
};
