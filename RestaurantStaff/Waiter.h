#pragma once
#include "Staff.h"
class Waiter : public Staff
{
public:
    Waiter(const std::string& name = "") : Staff(name) {}
};

