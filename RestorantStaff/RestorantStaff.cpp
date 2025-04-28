#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include "Staff.h"
#include "Cleaner.h"
#include "ChiefCooker.h"
#include "PastyCook.h"
#include "Sushef.h"
#include "Hostess.h"

using namespace std;



// ========== Работа с деревом и командами ==========

map<string, vector<shared_ptr<Staff>>> tree = {
    {"Cleaner", {}}, {"ChiefCooker", {}}, {"PastyCook", {}}, {"Sushef", {}}, {"Hostess", {}}
};

string currentNode;

bool isLeaf(const string& node) {
    return node == "Cleaner" || node == "ChiefCooker" || node == "PastyCook" || node == "Sushef" || node == "Hostess";
}

void cmdTREE() {
    cout << "Staff\n"
        << " |- Cleaner\n"
        << " |- Cook\n"
        << "    |- ChiefCooker\n"
        << "    |- PastyCook\n"
        << " |- Waiter\n"
        << "    |- MainWaiter\n"
        << "       |- Hostess\n"
        << "    |- Sushef\n";
}

void cmdCD(const string& node) {
    if (isLeaf(node)) {
        currentNode = node;
        cout << "Moved to " << node << endl;
    }
    else {
        cout << "Cannot move to " << node << ". Only leaf classes allowed.\n";
    }
}

// (Далее идут команды MO, DO, MDO, DIR, SHOW, SAVE, READ, menu() и main())

// Создание нового объекта
void cmdMO(const string& objName) {
    if (!isLeaf(currentNode)) {
        cout << "Cannot create object here! Only in leaf nodes.\n";
        return;
    }

    // Проверка на уникальность имени
    for (auto& obj : tree[currentNode]) {
        if (obj->getName() == objName) {
            cout << "An object with this name already exists. Creation aborted.\n";
            return;
        }
    }

    if (currentNode == "Cleaner") {
        int speed, salary;
        cout << "Enter Speed: ";
        if (!(cin >> speed)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input.\n"; return; }
        cout << "Enter Salary: ";
        if (!(cin >> salary)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input.\n"; return; }
        tree[currentNode].push_back(make_shared<Cleaner>(objName, speed, salary));
    }
    else if (currentNode == "ChiefCooker") {
        string cuisine;
        int dishes, experience;
        cout << "Enter Cuisine: ";
        if (!(cin >> cuisine)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input.\n"; return; }
        cout << "Enter Dishes/hour: ";
        if (!(cin >> dishes)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input.\n"; return; }
        cout << "Enter Experience: ";
        if (!(cin >> experience)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input.\n"; return; }
        tree[currentNode].push_back(make_shared<ChiefCooker>(objName, cuisine, dishes, experience));
    }
    else if (currentNode == "PastyCook") {
        string cuisine;
        int cakes, skill;
        cout << "Enter Cuisine: ";
        if (!(cin >> cuisine)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input.\n"; return; }
        cout << "Enter Cakes/day: ";
        if (!(cin >> cakes)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input.\n"; return; }
        cout << "Enter Skill: ";
        if (!(cin >> skill)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input.\n"; return; }
        tree[currentNode].push_back(make_shared<PastyCook>(objName, cuisine, cakes, skill));
    }
    else if (currentNode == "Sushef") {
        string language;
        int specialOrders, accuracy;
        cout << "Enter Language: ";
        if (!(cin >> language)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input.\n"; return; }
        cout << "Enter Special Orders: ";
        if (!(cin >> specialOrders)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input.\n"; return; }
        cout << "Enter Accuracy: ";
        if (!(cin >> accuracy)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input.\n"; return; }
        tree[currentNode].push_back(make_shared<Sushef>(objName, language, specialOrders, accuracy));
    }
    else if (currentNode == "Hostess") {
        string language;
        int tables, greetScore, friendliness;
        cout << "Enter Language: ";
        if (!(cin >> language)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input.\n"; return; }
        cout << "Enter Tables: ";
        if (!(cin >> tables)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input.\n"; return; }
        cout << "Enter Greeting Score: ";
        if (!(cin >> greetScore)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input.\n"; return; }
        cout << "Enter Friendliness: ";
        if (!(cin >> friendliness)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input.\n"; return; }
        tree[currentNode].push_back(make_shared<Hostess>(objName, language, tables, greetScore, friendliness));
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Удаление объекта
void cmdDO(const string& objName) {
    auto& objs = tree[currentNode];
    objs.erase(remove_if(objs.begin(), objs.end(), [&](auto& obj) { return obj->getName() == objName; }), objs.end());
    cout << "Deleted (if existed): " << objName << endl;
}

// Модификация объекта
void cmdMDO(const string& objName) {
    if (objName.empty()) {
        cout << "Please specify object name.\n";
        return;
    }

    for (auto& obj : tree[currentNode]) {
        if (obj->getName() == objName) {
            obj->modify();
            return;
        }
    }

    cout << "Object not found.\n";
}

// Показ списка объектов
void cmdDIR() {
    if (tree.find(currentNode) != tree.end()) {
        for (auto& obj : tree[currentNode])
            cout << obj->getName() << endl;
    }
}

// Показ деталей объекта
void cmdSHOW(const string& objName) {
    for (auto& obj : tree[currentNode]) {
        if (obj->getName() == objName) {
            obj->show();
            return;
        }
    }
    cout << "Object not found.\n";
}

// Сохранение всех объектов в файл
void cmdSAVE() {
    ofstream ofs("staff.txt");
    if (!ofs.is_open()) {
        cout << "Error: Cannot open staff.txt\n";
        return;
    }

    for (auto it = tree.begin(); it != tree.end(); ++it) {
        for (auto& obj : it->second) {
            obj->save(ofs);
        }
    }
    ofs.close();
    cout << "Saved to staff.txt\n";
}


// Загрузка объектов из файла
void cmdREAD() {
    ifstream ifs("staff.txt");
    if (!ifs.is_open()) {
        cout << "Error: Cannot open staff.txt\n";
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
            int specialOrders, accuracy;
            ifs >> name >> language >> specialOrders >> accuracy;
            tree["Sushef"].push_back(make_shared<Sushef>(name, language, specialOrders, accuracy));
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

// Меню команд
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

// Главная функция
int main() {
    menu();
    return 0;
}
