#pragma once
#include "Staff.h"
class Cook : public Staff
{
public:
    Cook(const std::string& name = "") : Staff(name) {}
};

