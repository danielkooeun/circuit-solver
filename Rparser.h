#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include "Resistor.h"
using namespace std;

void Parser();
bool testConverter(string test, int& real);
bool testConverterDouble(string test, double& real);

#endif /* PARSER_H */

