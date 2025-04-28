#pragma once
#include "Staff.h" // обязательно подключаем базовый класс
#include <iostream>

class Cleaner : public Staff {
private:
    int speed;
protected:
    int salary;
public:
    Cleaner(const string& name = "", int speed = 0, int salary = 0);
    void show() const override;
    void save(ostream& os) const override;
    void modify() override;
};
