#ifndef NODE_H
#define NODE_H

#include "ResistorList.h"


class Node {
private:
    int id;
    int numRes;
    ResistorList* resistors;
    bool vset;
    double voltage;
    Node* next;

public:
    // constructors
    Node();
    Node(int id_, Node* next_);
    Node(const Node& other);        // Copy constructor
    ~Node();
    
    void print() const;
    int getId() const;
    int getNumRes() const;
    Node* getNext() const;
    double getV() const;
    ResistorList* getRList() const;
    Resistor* getRHead() const;
    bool getVset() const;
    void setNext(Node* next_);
    void setV(double voltage_);
    void setVset(double voltage_);
    void unsetV();
    void addR(string label_, double resistance_, int node1_, int node2_);
    void deleteR(string label_);
};

#endif	/* NODE_H */

