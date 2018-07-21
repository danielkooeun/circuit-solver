#ifndef RESISTORLIST_H
#define RESISTORLIST_H

#include <string>
#include "Resistor.h"
using namespace std;


class ResistorList {
private:
    Resistor* head;
public:
    // constructors
    ResistorList();
    ~ResistorList();
    
    void printList() const;
    Resistor* findR(string label_) const;
    Resistor* getHead() const;
    void insertR(string label_, double resistance_, int end1_, int end2_);
    bool changeR(string label_, double resistance_);    // returns FALSE if label does not exist
    void deleteR(string label_);
};

#endif /* RESISTORLIST_H */
