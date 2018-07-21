#include <iostream>
#include <iomanip>
#include "Resistor.h"
using namespace std;

// Resistor constructor
Resistor::Resistor(string label_, double resistance_, int end1_, int end2_) {
    label = label_;
    resistance = resistance_;
    endpoints[0] = end1_;
    endpoints[1] = end2_;
    next = NULL;
}


Resistor::~Resistor() {
}

// Getter functions
string Resistor::getName() const {
    return label;
}

double Resistor::getR() const {
    return resistance;
}


Resistor* Resistor::getNext() const {
    return next;
}

int Resistor::getPoints(int id_) const {
    if (endpoints[0] == id_)
        return endpoints[1];
    else if (endpoints[1] == id_)
        return endpoints[0];
    else
        return id_;
}

// Setter functions
void Resistor::setR(double resistance_) {
    resistance = resistance_;
}

void Resistor::setNext(Resistor* next_) {
    next = next_;
}

// Resistor print
void Resistor::printR() {
    cout << label << setw(20) << fixed << setprecision(2) << resistance << " Ohms " << endpoints[0] << " -> " << endpoints[1] << endl;
}