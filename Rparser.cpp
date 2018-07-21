#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include "Rparser.h"
#include "Node.h"
#include "NodeList.h"
#include "Resistor.h"
#include "ResistorList.h"
using namespace std;

#define MIN_ITERATION_CHANGE 0.0001



void Parser() {
    string line, command;

    NodeList* nodeList = new NodeList();

    // ERROR LIST:
    string eTooFew = "Error: too few arguments";
    string eTooMany = "Error: too many arguments";
    string eRName = "Error: resistor name cannot be the keyword \"all\"";
    string eNegRes = "Error: negative resistance";

    cout << "> ";
    getline(cin, line); // Get a line from standard input
    while (!cin.eof()) {

        string name;
        double resistance = -1;

        stringstream lineStream(line);
        lineStream >> command;

        // Sets voltage for node (already existing)
        if (command == "setV") {
            int nodeid = -1;
            double voltage = -1;

            lineStream >> nodeid >> voltage;
            
            // Error to check if node exists
            if (nodeList->findNode(nodeid) == NULL)
                cout << "Error: node " << nodeid << " not found" << endl;
            
            else {
                nodeList->findOrInsert(nodeid)->setVset(voltage);
                cout << "Set: node " << nodeid << " to " << setprecision(2) << fixed << voltage << " Volts" << endl;
            }
        }
        
        // Removes set voltage boolean for node (false)
        else if (command == "unsetV") {
            int nodeid = -1;

            lineStream >> nodeid;
            
            if (nodeList->findNode(nodeid) == NULL)
                cout << "Error: node " << nodeid << " not found" << endl;
            
            else {
                nodeList->findNode(nodeid)->unsetV();
                cout << "Unset: the solver will determine the voltage of node " << nodeid << endl;
            }
        }
        
        // Solve() function for nodes
        else if (command == "solve") {
            
            if (nodeList->solveCheck())
                cout << "Error: no nodes have their voltage set" << endl;
            
            else {
                double change = 1;
                while (change > MIN_ITERATION_CHANGE)
                    change = nodeList->solve();

                cout << "Solve:" << endl;
                nodeList->solvePrint();
            }
        }
        
        // insert resistor
        else if (command == "insertR") {
            int nodeid1 = -1;
            int nodeid2 = -1;
            string resistanceTest;
            string nodeid1Test;
            string nodeid2Test;
            bool testOne = false;
            bool testTwo = false;
            bool testThree = false;

            lineStream >> name >> resistanceTest >> nodeid1Test >> nodeid2Test;

            if (name == "all")
                cout << eRName << endl;

            else
                // need to get test values -> real values
                testThree = testThree = testConverterDouble(resistanceTest, resistance);

            if (testThree) {
                testOne = testConverter(nodeid1Test, nodeid1);
                if (testOne)
                    testTwo = testConverter(nodeid2Test, nodeid2);
            }

            if (testOne && testTwo && testThree) {
                if (lineStream.fail()) {
                    if ((name.empty() || resistanceTest.empty() || nodeid1Test.empty() || nodeid2Test.empty()))
                        cout << eTooFew << endl;
                }

                else {
                    // Test for whether there are extra arguments
                    string dummy;
                    lineStream >> dummy;

                    if (!dummy.empty())
                        cout << eTooMany << endl;

                    else {
                        int nodes[2] = {nodeid1, nodeid2};

                        // Check for existing name
                        if (nodeList->nameCheck(name))
                            cout << "Error: resistor " << name << " already exists" << endl;


                        // Nodes equal error
                        else if (nodeid1 == nodeid2)
                            cout << "Error: both terminals of resistor connect to node " << nodeid1 << endl;

                        else {
                            nodeList->findOrInsert(nodeid1)->addR(name, resistance, nodeid1, nodeid2);
                            nodeList->findOrInsert(nodeid2)->addR(name, resistance, nodeid1, nodeid2);

                            cout << "Inserted: resistor " << name << " " << setprecision(2) << fixed << resistance << " Ohms " << nodeid1 << " -> " << nodeid2 << endl;
                        }
                    }
                }

            }
        }
        
        // modifies resistance value
        else if (command == "modifyR") {
            string resistanceTest;
            bool testOne = false;

            lineStream >> name >> resistanceTest;

            if (name == "all")
                cout << eRName << endl;
            else
                testOne = testConverterDouble(resistanceTest, resistance);

            if (testOne) {
                if (lineStream.fail()) {
                    // test for invalid argument
                    if (name.empty() || resistance == -1)
                        cout << eTooFew << endl;
                } else {
                    // Test for whether there are extra arguments
                    string dummy;
                    lineStream >> dummy;

                    if (resistance < 0)
                        cout << eNegRes << endl;

                    else if (!dummy.empty())
                        cout << eTooMany << endl;

                    else {
                        if (!(nodeList->nameCheck(name)))
                            cout << "Error: resistor " << name << " not found" << endl;
                        
                        else {
                            double lastRes = nodeList->getR(name)->getR();
                            nodeList->modifyR(name, resistance);
                            
                            cout << "Modified: resistor " << name << " from " << setprecision(2) << fixed << lastRes << " Ohms to " << resistance << " Ohms" << endl;
                        }
                    }
                }
            }

        }
        
        // Print resistor function
        else if (command == "printR") {
            lineStream >> name;

            if (lineStream.fail()) {
                // test for too few arguments
                cout << eTooFew << endl;
            }
            
            else {
                // Test for whether there are extra arguments
                string dummy;
                lineStream >> dummy;
                
                if (!dummy.empty())
                    cout << eTooMany << endl;
                
                else {
                    if (!(nodeList->nameCheck(name)))
                            cout << "Error: resistor " << name << " not found" << endl;
                    
                    else {
                        cout << "Print:" << endl;
                        nodeList->printR(name);
                    }
                }
            }
        }
        
        // prints existing node's resistors
        else if (command == "printNode") {
            string intOrString;
            lineStream >> intOrString;

            if (lineStream.fail()) {
                // test for too few arguments
                cout << eTooFew << endl;
            }
            
            else {
                int nodeid;
                bool test = true;

                if (intOrString != "all")
                    test = testConverter(intOrString, nodeid);
                
                if (test && (nodeList->findNode(nodeid) == NULL) && intOrString != "all")
                    cout << "Error: node " << nodeid << " not found" << endl;

                else if (test) {
                    string dummy;
                    lineStream >> dummy;

                    // Test for whether there are extra arguments
                    if (!dummy.empty())
                        cout << eTooMany << endl;

                    else if (intOrString == "all") {
                        cout << "Print:" << endl;
                        nodeList->printAll();
                    }
                    
                    else {
                        cout << "Print:" << endl;
                        nodeList->findNode(nodeid)->print();
                    }
                }
            }
        }
        
        // deletes resistors
        else if (command == "deleteR") {
            string dummy;
            lineStream >> name;

            // Test for whether there are too few arguments
            if (lineStream.fail())
                cout << eTooFew << endl;

            else {
                // Test for whether there are extra arguments
                lineStream >> dummy;
                if (!dummy.empty())
                    cout << eTooMany << endl;
                
                else if (!(nodeList->nameCheck(name)) && (name != "all"))
                    cout << "Error: resistor " << name << " not found" << endl;

                else if (name == "all") {
                    delete nodeList;
                    nodeList = new NodeList();
                    cout << "Deleted: all resistors" << endl;
                }
                
                else {
                    nodeList->deleteR(name);
                    cout << "Deleted: resistor " << name << endl;
                }
            }
        }
        
        else {
            cout << "Error: invalid command" << endl;
        }

        // Clear remainder of stream and error flags
        lineStream.clear();
        lineStream.ignore(1000, '\n');

        cout << "> ";
        getline(cin, line);

    } // End input loop until EOF.
    
    delete nodeList;
    return;
}

// Function to test each NODE input for being an INT
bool testConverter(string test, int& real) {
    stringstream converter(test);

    // dummy variable to test if there is more to the stream left
    string remainder;

    // if test is empty, then too few arguments    
    converter >> real;
    
    if (converter.fail()) {
        cout << "Error: invalid argument" << endl;
        return false;
    }
    
    converter >> remainder;
    if (!remainder.empty()) {
        cout << "Error: invalid argument" << endl;
        return false;
    }
    
    return true;
}

// Function to test each RESISTOR input for being a DOUBLE. not negative
bool testConverterDouble(string test, double& real) {
    stringstream converter(test);

    // dummy variable to test if there is more to the stream left
    string remainder;

    // if test is empty, then too few arguments
    if (test.empty())
        return true;

        converter >> real;

        if (converter.fail()) {
            cout << "Error: invalid argument" << endl;
            return false;
        }

    converter >> remainder;
    if (!remainder.empty()) {
        cout << "Error: invalid argument" << endl;
        return false;
    }

    if (real < 0) {
        cout << "Error: negative resistance" << endl;
        return false;
    }
    return true;
}
