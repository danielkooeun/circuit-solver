#include <string>
#include "ResistorList.h"


// ResistorList constructor
ResistorList::ResistorList() {
    head = NULL;
}

// ResistorList destructor - deletes all resistors inside
ResistorList::~ResistorList() {
    Resistor* traverse = head;
    
    while (traverse != NULL) {
        Resistor* next = NULL;
        
        if (traverse->getNext() != NULL)
            next = traverse->getNext();
        
        delete traverse;
        traverse = next;
    }
}

// Returns resistor with name
Resistor* ResistorList::findR(string label_) const {
    Resistor* traverse = head;
    
    while (traverse != NULL) {
        if (traverse->getName() == label_)
            return traverse;
        
        else
            traverse = traverse->getNext();
    }
    
    return NULL;
}

// Returns resistor* head
Resistor* ResistorList::getHead() const {
    return head;
}

// Inserts resistor into nodes
void ResistorList::insertR(string label_, double resistance_, int end1_, int end2_) {
    Resistor* traverse = head;
    Resistor* last = head;
    
    while (traverse != NULL) {
        last = traverse;
        traverse = traverse->getNext();
    }
    
    if (head == NULL)
        head = new Resistor(label_, resistance_, end1_, end2_);
    
    else
        last->setNext(new Resistor(label_, resistance_, end1_, end2_));
}

// ModifyR function
bool ResistorList::changeR(string label_, double resistance_) {
    Resistor* traverse = head;
    while (traverse != NULL) {
        if (traverse->getName() == label_) {
            traverse->setR(resistance_);
            return true;
        }
        else
            traverse = traverse->getNext();
    }
    return false;
}

// Delete resistor with certain name
void ResistorList::deleteR(string label_) {
    Resistor* traverse = head;
    Resistor* last = NULL;
    
    while (traverse != NULL) {
        if (traverse->getName() == label_) {
            if (last != NULL)
                last->setNext(traverse->getNext());
            
            if (traverse == head)
                head = head->getNext();
            
            delete traverse;
            return;
        }
        
        else {
            last = traverse;
            traverse = traverse->getNext();
        }
    }
}

