#ifndef NODELIST_H
#define NODELIST_H

#include "Node.h"


class NodeList {
private:
    Node* head;
public:
    // constructors
    NodeList();
    ~NodeList();
    
    
    
    Node* findNode(int id) const;
    bool nameCheck(string name_) const;
    Node* findOrInsert(int id_);
    Node* setVset(int id_, double voltage_);
    double solve();
    void solvePrint();
    bool solveCheck();
    void modifyR(string name_, double resistance_);
    void printR(string name_) const;
    Resistor* getR(string name_) const;
    void printAll() const;
    void deleteR(string name_);
};

#endif /* NODELIST_H */

