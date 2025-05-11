#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Staff.h"
#include "Cleaner.h"
#include "ChiefCooker.h"
#include "PastyCook.h"
#include "Sushef.h"
#include "Hostess.h"

using namespace std;


const string file_name = "staff.txt";

// ========== Working with the tree and commands ==========

map<string, vector<shared_ptr<Staff>>> tree = {
    {"Cleaner", {}}, {"ChiefCooker", {}}, {"PastyCook", {}}, {"Sushef", {}}, {"Hostess", {}}
};

string currentNode;

bool isLeaf(const string& node) {
    if (node == "Cleaner" || node == "ChiefCooker" || node == "PastyCook" || node == "Sushef" || node == "Hostess") {
        return true;
    }
    else {
        return false;
    }
}

void cmdTREE() {
    cout << "Staff\n"
        << " |- Cleaner\n"
        << " |- Cook\n"
        << "    |- ChiefCooker\n"
        << "      |- Sushef\n"
        << "    |- PastyCook\n"
        << " |- Waiter\n"
        << "    |- MainWaiter\n"
        << "       |- Hostess\n";

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

// (The following commands are MO, DO, MDO, DIR, SHOW, SAVE, READ, menu() and main())

// Create a new object
int getIntInput(const string& prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        cout << "Invalid input. Please try again: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n');
    return value;
}

void cmdMO(const string& objName) {
    if (!isLeaf(currentNode)) {
        cout << "Cannot create object here! Only in leaf nodes.\n";
        return;
    }

    for (auto& obj : tree[currentNode]) {
        if (obj->getName() == objName) {
            cout << "An object with this name already exists. Creation aborted.\n";
            return;
        }
    }

    if (currentNode == "Cleaner") {
        int speed = getIntInput("Enter Speed: ");
        int salary = getIntInput("Enter Salary: ");
        tree[currentNode].push_back(make_shared<Cleaner>(objName, speed, salary));
    }
    else if (currentNode == "ChiefCooker") {
        string cuisine;
        cout << "Enter Cuisine: ";
        cin >> cuisine;
        int dishes = getIntInput("Enter Dishes/hour: ");
        int experience = getIntInput("Enter Experience: ");
        tree[currentNode].push_back(make_shared<ChiefCooker>(objName, cuisine, dishes, experience));
    }
    else if (currentNode == "PastyCook") {
        string cuisine;
        cout << "Enter Cuisine: ";
        cin >> cuisine;
        int cakes = getIntInput("Enter Cakes/day: ");
        int skill = getIntInput("Enter Skill: ");
        tree[currentNode].push_back(make_shared<PastyCook>(objName, cuisine, cakes, skill));
    }
    else if (currentNode == "Sushef") {
        string language;
        cout << "Enter Language: ";
        cin >> language;
        int specialOrders = getIntInput("Enter Special Orders: ");
        int accuracy = getIntInput("Enter Accuracy: ");
        tree[currentNode].push_back(make_shared<Sushef>(objName, language, specialOrders, accuracy));
    }
    else if (currentNode == "Hostess") {
        string language;
        cout << "Enter Language: ";
        cin >> language;
        int tables = getIntInput("Enter Tables: ");
        int greetScore = getIntInput("Enter Greeting Score: ");
        int friendliness = getIntInput("Enter Friendliness: ");
        tree[currentNode].push_back(make_shared<Hostess>(objName, language, tables, greetScore, friendliness));
    }
}

// Deleting an object
void cmdDO(const string& objName) {
    auto& objs = tree[currentNode];
    objs.erase(remove_if(objs.begin(), objs.end(), [&](auto& obj) { return obj->getName() == objName; }), objs.end());
    cout << "Deleted (if existed): " << objName << endl;
}

// Object modification
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

// Show list of objects
void cmdDIR() {
    if (tree.find(currentNode) != tree.end()) {
        for (auto& obj : tree[currentNode])
            cout << obj->getName() << endl;
    }
}

// Show object details
void cmdSHOW(const string& objName) {
    for (auto& obj : tree[currentNode]) {
        if (obj->getName() == objName) {
            obj->show();
            return;
        }
    }
    cout << "Object not found.\n";
}

// Save all objects to file
void cmdSAVE() {
    ofstream ofs(file_name);
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


// Load objects from file
void cmdREAD() {
    ifstream ifs(file_name);
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

// Command menu
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

// Main function
int main() {
    menu();
    return 0;
}
