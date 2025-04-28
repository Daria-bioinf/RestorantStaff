#pragma once
#include <iostream>
#include <string>

using namespace std;

class Staff {
protected:
    string name;
public:
    Staff(const string& name = "");
    virtual ~Staff();

    string getName() const;
    void setName(const string& newName);

    virtual void show() const = 0;
    virtual void save(ostream& os) const = 0;
    virtual void modify() = 0;
};
