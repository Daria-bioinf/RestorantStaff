// PastyCook.h
#pragma once
#include "Staff.h"
#include <iostream>
#include <string>

class PastyCook : public Staff {
protected:
    string cuisine;
private:
    int cakesPerDay;
    int skill;
public:
    PastyCook(const string& name = "", const string& cuisine = "", int cakes = 0, int skill = 0);

    void show() const override;
    void save(ostream& os) const override;
    void modify() override;
};