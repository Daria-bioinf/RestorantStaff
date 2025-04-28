// Hostess.h
#pragma once
#include "Staff.h"
#include <iostream>
#include <string>

class Hostess : public Staff {
protected:
    string language;
private:
    int tables;
    int greetingScore;
    int friendliness;
public:
    Hostess(const string& name = "", const string& language = "", int tables = 0, int greet = 0, int friendly = 0);

    void show() const override;
    void save(ostream& os) const override;
    void modify() override;
};
