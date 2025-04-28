#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// Базовый класс Staff
class Staff {
protected:
    string position;
private:
    string name;
public:
    Staff(string name = "", string position = "") : name(name), position(position) {}
    virtual ~Staff() {}
    virtual void show() const = 0;
    virtual void save(ostream& os) const = 0;
    virtual void modify() = 0;
    string getName() const { return name; }
    void setName(const string& n) { name = n; }
};

// Cleaner (лист)
class Cleaner : public Staff {
private:
    int speed;
protected:
    int salary;
public:
    Cleaner(string name = "", int speed = 0, int salary = 0)
        : Staff(name, "Cleaner"), speed(speed), salary(salary) {
    }
    void show() const override {
        cout << "Cleaner: " << getName() << ", Speed: " << speed << ", Salary: " << salary << endl;
    }
    void save(ostream& os) const override {
        os << "Cleaner " << getName() << " " << speed << " " << salary << endl;
    }
    void modify() override {
        cout << "New Speed and Salary: ";
        cin >> speed >> salary;
    }
};

// Cook
class Cook : public Staff {
protected:
    string cuisine;
public:
    Cook(string name = "", string cuisine = "")
        : Staff(name, "Cook"), cuisine(cuisine) {
    }
};

// ChiefCooker (лист)
class ChiefCooker : public Cook {
private:
    int dishesPerHour;
protected:
    int experience;
public:
    ChiefCooker(string name = "", string cuisine = "", int dishes = 0, int exp = 0)
        : Cook(name, cuisine), dishesPerHour(dishes), experience(exp) {
    }
    void show() const override {
        cout << "ChiefCooker: " << getName() << ", Cuisine: " << cuisine
            << ", Dishes/hour: " << dishesPerHour << ", Experience: " << experience << endl;
    }
    void save(ostream& os) const override {
        os << "ChiefCooker " << getName() << " " << cuisine << " "
            << dishesPerHour << " " << experience << endl;
    }
    void modify() override {
        cout << "New Cuisine, Dishes/hour and Experience: ";
        cin >> cuisine >> dishesPerHour >> experience;
    }
};

// PastyCook (лист)
class PastyCook : public Cook {
private:
    int cakesPerDay;
protected:
    int skill;
public:
    PastyCook(string name = "", string cuisine = "", int cakes = 0, int skill = 0)
        : Cook(name, cuisine), cakesPerDay(cakes), skill(skill) {
    }
    void show() const override {
        cout << "PastyCook: " << getName() << ", Cuisine: " << cuisine
            << ", Cakes/day: " << cakesPerDay << ", Skill: " << skill << endl;
    }
    void save(ostream& os) const override {
        os << "PastyCook " << getName() << " " << cuisine << " "
            << cakesPerDay << " " << skill << endl;
    }
    void modify() override {
        cout << "New Cuisine, Cakes/day and Skill: ";
        cin >> cuisine >> cakesPerDay >> skill;
    }
};

// Waiter
class Waiter : public Staff {
protected:
    string language;
public:
    Waiter(string name = "", string language = "")
        : Staff(name, "Waiter"), language(language) {
    }
};

// MainWaiter
class MainWaiter : public Waiter {
protected:
    int tables;
public:
    MainWaiter(string name = "", string language = "", int tables = 0)
        : Waiter(name, language), tables(tables) {
    }
};

// Hostess (лист)
class Hostess : public MainWaiter {
private:
    int friendliness;
protected:
    int greetingScore;
public:
    Hostess(string name = "", string language = "", int tables = 0, int greet = 0, int friendly = 0)
        : MainWaiter(name, language, tables), greetingScore(greet), friendliness(friendly) {
    }
    void show() const override {
        cout << "Hostess: " << getName() << ", Language: " << language
            << ", Tables: " << tables << ", Greeting: " << greetingScore
            << ", Friendliness: " << friendliness << endl;
    }
    void save(ostream& os) const override {
        os << "Hostess " << getName() << " " << language << " "
            << tables << " " << greetingScore << " " << friendliness << endl;
    }
    void modify() override {
        cout << "New Language, Tables, Greeting Score and Friendliness: ";
        cin >> language >> tables >> greetingScore >> friendliness;
    }
};

// Sushef (лист)
class Sushef : public Waiter {
private:
    int specialOrders;
protected:
    int accuracy;
public:
    Sushef(string name = "", string language = "", int orders = 0, int accuracy = 0)
        : Waiter(name, language), specialOrders(orders), accuracy(accuracy) {
    }
    void show() const override {
        cout << "Sushef: " << getName() << ", Language: " << language
            << ", Special Orders: " << specialOrders << ", Accuracy: " << accuracy << endl;
    }
    void save(ostream& os) const override {
        os << "Sushef " << getName() << " " << language << " "
            << specialOrders << " " << accuracy << endl;
    }
    void modify() override {
        cout << "New Language, Special Orders and Accuracy: ";
        cin >> language >> specialOrders >> accuracy;
    }
};

// Дерево структуры
map<string, vector<shared_ptr<Staff>>> tree = {
    {"Cleaner", {}}, {"ChiefCooker", {}}, {"PastyCook", {}},
    {"Sushef", {}}, {"Hostess", {}}
};

// Навигация
string currentNode;

// Проверка: является ли узел листом
bool isLeaf(const string& node) {
    return (node == "Cleaner" || node == "ChiefCooker" || node == "PastyCook" || node == "Sushef" || node == "Hostess");
}

// Показ структуры
void cmdTREE() {
    cout << "Staff\n";
    cout << " |- Cleaner\n";
    cout << " |- Cook\n";
    cout << "    |- ChiefCooker\n";
    cout << "    |- PastyCook\n";
    cout << " |- Waiter\n";
    cout << "    |- MainWaiter\n";
    cout << "       |- Hostess\n";
    cout << "    |- Sushef\n";
}

void cmdCD(const string& node) {
    currentNode = node;
    cout << "Moved to " << node << endl;
}

void cmdMO(const string& objName) {
    if (!isLeaf(currentNode)) {
        cout << "Cannot create object here! Only in leaf nodes.\n";
        return;
    }
    if (currentNode == "Cleaner") {
        int speed, salary;
        cout << "Enter Speed and Salary: ";
        cin >> speed >> salary;
        tree[currentNode].push_back(make_shared<Cleaner>(objName, speed, salary));
    }
    else if (currentNode == "ChiefCooker") {
        string cuisine;
        int dishes, experience;
        cout << "Enter Cuisine, Dishes/hour, Experience: ";
        cin >> cuisine >> dishes >> experience;
        tree[currentNode].push_back(make_shared<ChiefCooker>(objName, cuisine, dishes, experience));
    }
    else if (currentNode == "PastyCook") {
        string cuisine;
        int cakes, skill;
        cout << "Enter Cuisine, Cakes/day, Skill: ";
        cin >> cuisine >> cakes >> skill;
        tree[currentNode].push_back(make_shared<PastyCook>(objName, cuisine, cakes, skill));
    }
    else if (currentNode == "Sushef") {
        string language;
        int orders, accuracy;
        cout << "Enter Language, SpecialOrders, Accuracy: ";
        cin >> language >> orders >> accuracy;
        tree[currentNode].push_back(make_shared<Sushef>(objName, language, orders, accuracy));
    }
    else if (currentNode == "Hostess") {
        string language;
        int tables, greet, friendly;
        cout << "Enter Language, Tables, Greeting, Friendliness: ";
        cin >> language >> tables >> greet >> friendly;
        tree[currentNode].push_back(make_shared<Hostess>(objName, language, tables, greet, friendly));
    }
}

void cmdDO(const string& objName) {
    auto& objs = tree[currentNode];
    objs.erase(remove_if(objs.begin(), objs.end(), [&](auto& obj) { return obj->getName() == objName; }), objs.end());
    cout << "Deleted (if existed): " << objName << endl;
}

void cmdMDO(const string& objName) {
    for (auto& obj : tree[currentNode]) {
        if (obj->getName() == objName) {
            obj->modify();
            return;
        }
    }
    cout << "Object not found.\n";
}

void cmdDIR() {
    if (isLeaf(currentNode)) {
        for (auto& obj : tree[currentNode])
            cout << obj->getName() << endl;
    }
    else {
        for (auto it = tree.begin(); it != tree.end(); ++it) {
            if (it->first.find(currentNode) != string::npos) {
                for (auto& obj : it->second)
                    cout << obj->getName() << endl;
            }
        }
    }
}


void cmdSHOW(const string& objName) {
    for (auto& obj : tree[currentNode]) {
        if (obj->getName() == objName) {
            obj->show();
            return;
        }
    }
    cout << "Object not found.\n";
}

void cmdSAVE() {
    ofstream ofs("staff.txt");
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        for (auto& obj : it->second) {
            obj->save(ofs);
        }
    }
    cout << "Saved to staff.txt\n";
}


void cmdREAD() {
    ifstream ifs("staff.txt");
    if (!ifs.is_open()) {
        cout << "Cannot open staff.txt\n";
        return;
    }
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        it->second.clear();
    }
    string type;
    while (ifs >> type) {
        if (type == "Cleaner") {
            string name;
            int speed, salary;
            ifs >> name >> speed >> salary;
            tree["Cleaner"].push_back(make_shared<Cleaner>(name, speed, salary));
        }
        else if (type == "ChiefCooker") {
            string name, cuisine;
            int dishes, experience;
            ifs >> name >> cuisine >> dishes >> experience;
            tree["ChiefCooker"].push_back(make_shared<ChiefCooker>(name, cuisine, dishes, experience));
        }
        else if (type == "PastyCook") {
            string name, cuisine;
            int cakes, skill;
            ifs >> name >> cuisine >> cakes >> skill;
            tree["PastyCook"].push_back(make_shared<PastyCook>(name, cuisine, cakes, skill));
        }
        else if (type == "Sushef") {
            string name, language;
            int orders, accuracy;
            ifs >> name >> language >> orders >> accuracy;
            tree["Sushef"].push_back(make_shared<Sushef>(name, language, orders, accuracy));
        }
        else if (type == "Hostess") {
            string name, language;
            int tables, greet, friendly;
            ifs >> name >> language >> tables >> greet >> friendly;
            tree["Hostess"].push_back(make_shared<Hostess>(name, language, tables, greet, friendly));
        }
    }
    ifs.close();
    cout << "Loaded from staff.txt\n";
}

void menu() {
    cout << "Commands: CD <node>, MO <name>, DO <name>, MDO <name>, DIR, SHOW <name>, SAVE, READ, TREE, EXIT\n";
    string line, cmd, arg;
    while (true) {
        cout << "[" << currentNode << "]> ";
        getline(cin, line);
        istringstream iss(line);
        iss >> cmd >> arg;
        if (cmd == "CD") cmdCD(arg);
        else if (cmd == "MO") cmdMO(arg);
        else if (cmd == "DO") cmdDO(arg);
        else if (cmd == "MDO") cmdMDO(arg);
        else if (cmd == "DIR") cmdDIR();
        else if (cmd == "SHOW") cmdSHOW(arg);
        else if (cmd == "SAVE") cmdSAVE();
        else if (cmd == "READ") cmdREAD();
        else if (cmd == "TREE") cmdTREE();
        else if (cmd == "EXIT") break;
        else cout << "Unknown command!\n";
    }
}

int main() {
    menu();
    return 0;
}
