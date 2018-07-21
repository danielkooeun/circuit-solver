#include <iostream>
#include <iomanip>
#include "Node.h"
#include "Resistor.h"
using namespace std;

// Node constructors
Node::Node() {
    id = 0;
    numRes = 0;
    resistors = new ResistorList();
    vset = false;
    voltage = 0;
    next = NULL;
}

Node::Node(int id_, Node* next_) {
    id = id_;
    numRes = 0;
    resistors = new ResistorList();
    vset = false;
    voltage = 0;
    next = next_;
}

// Node destructor
Node::~Node(){
    delete resistors;
}

// Node print
void Node::print() const {
    Resistor* traverse = resistors->getHead();
    
    cout << "Connections at node " << id << ": " << numRes << " resistor(s)" << endl;
    
    while (traverse != NULL) {
        cout << "  ";
        traverse->printR();
        traverse = traverse->getNext();
    }
    
}


// Getter functions
int Node::getId() const {
    return id;
}

int Node::getNumRes() const {
    return numRes;
}

Node* Node::getNext() const {
    return next;
}

double Node::getV() const {
    return voltage;
}

bool Node::getVset() const {
    return vset;
}

ResistorList* Node::getRList() const {
    return resistors;
}

Resistor* Node::getRHead() const {
    return resistors->getHead();
}

// Setter functions
void Node::setNext(Node* next_) {
    // Be careful to keep track of the current 'next' node
    next = next_;
};

void Node::setV(double voltage_) {
    voltage = voltage_;
}

void Node::setVset(double voltage_) {
    voltage = voltage_;
    vset = true;
}

void Node::unsetV() {
    voltage = 0;
    vset = false;
}

// Add resistor to Node
void Node::addR(string label_, double resistance_, int node1_, int node2_) {
    // Which ID is the first and last?
    resistors->insertR(label_, resistance_, node1_, node2_);
    numRes++;
}

// Delete resistor in Node
void Node::deleteR(string label_) {
    if (resistors->findR(label_) != NULL) {
        resistors->deleteR(label_);
        numRes--;
    }
}