#ifndef RESISTOR_H
#define RESISTOR_H

#include <string>
using namespace std;


class Resistor {
private:
    string label;
    double resistance;
    int endpoints[2];
    Resistor* next;

public:
    // constructors
    Resistor(string label_, double resistance_, int end1_, int end2_);
    ~Resistor();
    
    string getName() const;
    double getR() const;
    Resistor* getNext() const;
    int getPoints(int id_) const;
    void setR(double resistance_);
    void setNext(Resistor* next_);
    void printR();;
};

#endif	/* RESISTOR_H */

