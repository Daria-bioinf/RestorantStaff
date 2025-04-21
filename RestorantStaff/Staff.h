#pragma once
#include <cstring>
#include <iostream>


class Staff
{
protected:
	char Name[20];
private:
	int ID;
	int Age;
public:
	Staff() {
		strcpy(Name, "No Name");
		ID = 0;
		Age = 0;
	}
	Staff(const char* name, int id, int age) {
		strncpy(Name, name, 19);
		Name[19] = '\0';
		ID = id;
		Age = age;
	}
	virtual ~Staff() {}

	virtual void Show() const {
		cout << "Name: " << Name << ", ID: " << ID << ", Age: " << Age << endl;
	}
};

