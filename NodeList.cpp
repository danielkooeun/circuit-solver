#include <iostream>
#include <iomanip>
#include <cmath>
#include "NodeList.h"
#include "Resistor.h"


NodeList::NodeList() {
    head = NULL;
}

NodeList::~NodeList() {
    Node* traverse = head;
    
    while (traverse != NULL) {
        Node* next = NULL;
        
        if (traverse->getNext() != NULL)
            next = traverse->getNext();
        
        delete traverse;
        traverse = next;
    }
}

// Finds node and returns pointer
Node* NodeList::findNode(int id_) const {
    Node* traverse = head;
    while (traverse != NULL) {
        if(traverse->getId() == id_)
            return traverse;
        else
            traverse = traverse->getNext();
    }
    return NULL;
}

// Checks if name exists -> returns true
bool NodeList::nameCheck(string name_) const {
    Node* traverse = head;
    
    while (traverse != NULL) {
        ResistorList* resList = traverse->getRList();
        
        if (resList->findR(name_) != NULL)
            return true;
        
        traverse = traverse->getNext();
    }
    
    return false;
}

// Find a node with certain id and sets the voltage
// OR creates new voltage with set voltage
Node* NodeList::findOrInsert(int id_) {
    Node* traverse = head;
    Node* last = NULL;
    bool finished = false;
    
    while (traverse != NULL && !finished) {
        if(traverse->getId() == id_) {
            return traverse;
        }
        
        else if (traverse->getId() > id_)          
            finished = true;
        
        else {
            last = traverse;
            traverse = traverse->getNext();
        }
    }
    
    if (head == NULL) {
        head = new Node(id_, NULL);
        return head;
    }
    
    if (finished) {
        if (traverse == head) {
            head = new Node(id_, traverse);
            return head;
        }
        
        last->setNext(new Node(id_, traverse));
        return last->getNext();
    }
    
    if (finished && (last == NULL)) {
        head = new Node(id_, traverse);
        return head;
    }
    
    if (traverse == NULL) {
        last->setNext(new Node(id_, NULL));
        return last->getNext();
    }
}

// For the solve command
double NodeList::solve() {
    double change = 0;
    Node* traverse = head;
    
    while (traverse != NULL) {
        if (!traverse->getVset()) {
            double init = traverse->getV();
            double eResistor = 0;
            double eCurrent = 0;            
            int id = traverse->getId();
            Resistor* traverseR = traverse->getRHead();
            
            while (traverseR != NULL) {
                double res = traverseR->getR();
                double volt = (*this).findNode(traverseR->getPoints(id))->getV();

                eResistor += (1 / res);
                eCurrent += (volt / res);
                
                traverseR = traverseR->getNext();
            }
            
            traverse->setV((1 / eResistor) * eCurrent);
            
            double tempChange = abs(traverse->getV() - init);
            if (tempChange > change)
                change = tempChange;
        }
        
        traverse = traverse->getNext();
    }
    
    return change;
}

// Prints nodes after solve()
void NodeList::solvePrint() {
    Node* traverse = head;
    
    while (traverse != NULL) {
        cout << "  ";
        cout << "Node " << traverse->getId() << ": " << setprecision(2) << fixed << traverse->getV() << " V" << endl;
        
        traverse = traverse->getNext();
    }
}

// Returns true if none of the nodes with resistors have voltage set
bool NodeList::solveCheck() {
    Node* traverse = head;
    
    while (traverse != NULL) {
        if (traverse->getVset() && (traverse->getNumRes() > 0))
            return false;
        
        traverse = traverse->getNext();
    }
    
    return true;
}

// Search resistor and modify
void NodeList::modifyR(string name_, double resistance_) {
    Node* traverse = head;
    
    while (traverse != NULL) {
        Resistor* traverseR = traverse->getRHead();
        
        while (traverseR != NULL) {
            if (traverseR->getName() == name_)
                traverseR->setR(resistance_);
            
            traverseR = traverseR->getNext();
        }
        
        traverse = traverse->getNext();
    }
}

// Resistor print
void NodeList::printR(string name_) const {
    Node* traverse = head;
    
    while (traverse != NULL) {
        ResistorList* resList = traverse->getRList();
        
        if (resList->findR(name_) != NULL) {
            resList->findR(name_)->printR();
            return;
        }
        
        traverse = traverse->getNext();
    }
}

// Resistor search
Resistor* NodeList::getR(string name_) const {
    Node* traverse = head;
    
    while (traverse != NULL) {
        ResistorList* resList = traverse->getRList();
        
        if (resList->findR(name_) != NULL) {
            return resList->findR(name_);
        }
        
        traverse = traverse->getNext();
    }
}

// Prints all nodes
void NodeList::printAll() const {
    Node* traverse = head;
    
    while (traverse != NULL) {
        if (traverse->getNumRes() > 0) {
            traverse->print();
        }
        
        traverse = traverse->getNext();
    }
}

// Finds nodes and deletes resistor
void NodeList::deleteR(string name_) {
    Node* traverse = head;
    
    while (traverse != NULL) {
        traverse->deleteR(name_);
        traverse = traverse->getNext();
    }
}