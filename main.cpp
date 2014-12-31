#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include "NodeList.h"
#include "ResistorList.h"
#include "Node.h"
#include "Resistor.h"
#include "Rparser.h"

using namespace std;

int main(int argc, char *argv[]) {
	NodeList *nL = new NodeList;
	/* Allocates a new node list, which contains nodes,
		which contains resistor lists, which contains resistors.
		These sub-structures are created in the constructors
		for each class. */
	
	string line, cmd;
	cout.setf(ios::fixed);
	cout.precision(2);
	cout << "> ";
	cout.flush();
	
	getline(cin, line);					// Get a line from input
	while(cin.fail() && !cin.eof()) {	// In case cin fails.
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Error: failed to parse line\n> ";
		continue;
	}
	
	while(!cin.eof()) {
		stringstream lineStream(line);
		lineStream >> cmd;		// read in command
		
		if(lineStream.fail()) {
			line = RestartAfterError("invalid command", lineStream);
			continue;			// nothing in stringstream; start over
		}
		
		string name;
		double resistance;
		int nodeA, nodeB;
		double voltage;
		string junk;
		/* Note: "junk" checks for extra arguments */
		
		if(cmd == "insertR") {		/* INSERTR COMMAND */
			lineStream >> name;
			line = CheckName(name, cmd, lineStream);
			if(line != "n")		continue;
		
			lineStream >> resistance;
			line = CheckResistance(resistance, lineStream);
			if(line != "n")		continue;
		
			lineStream >> nodeA;
			line = CheckNode(nodeA, cmd, line, lineStream);
			if(line != "n")		continue;
		
			lineStream >> nodeB;
			line = CheckNode(nodeB, cmd, line, lineStream);
			if(line != "n")		continue;
		
			if(nodeA == nodeB) {
				cout << "Error: both terminals of resistor connect to node " << nodeA << "\n> ";
				cout.flush();
				line = RestartAfterError("n", lineStream);
				continue;
			}
		
			lineStream >> junk;
			line = CheckJunk(lineStream);
			if(line != "n")		continue;
			
			int nodes[2];
			nodes[0] = nodeA;
			nodes[1] = nodeB;
			
			/* If resistor already exists */
			if(nL->findRes(name) != NULL) {
				cout << "Error: resistor " << name << " already exists\n> ";
				cout.flush();
				line = RestartAfterError("n", lineStream);
				continue;
			}
			
			/* Finds or inserts node if it doesn't already exist.
				Then inserts a resistor into that node's resistor list. */
			Node **ptrA = nL->findOrInsert(nodeA);
			((*ptrA)->getrList())->insertRes(name, resistance, nodes);
			Node **ptrB = nL->findOrInsert(nodeB);
			((*ptrB)->getrList())->insertRes(name, resistance, nodes);

		
			cout << "Inserted: resistor " << name << " " << resistance << " Ohms " << nodeA << " -> " << nodeB << "\n> ";
			cout.flush();
		}
	
		else if(cmd == "modifyR") {		/* MODIFYR COMMAND */
			double old;
			lineStream >> name;
			line = CheckName(name, cmd, lineStream);
			if(line != "n")		continue;
		
			lineStream >> resistance;
			line = CheckResistance(resistance, lineStream);
			if(line != "n")		continue;
		
			lineStream >> junk;
			line = CheckJunk(lineStream);
			if(line != "n")		continue;
			
			/* Gets old resistance */
			Resistor **resptr = nL->findRes(name);
			if(resptr != NULL)	old = (*resptr)->getResistance();
			
			/* Modifies resistance. If returns false, resistance was not found */
			if(!(nL->modifyRes(name, resistance))) {
				cout << "Error: resistor " << name << " not found\n> ";
				cout.flush();
				line = RestartAfterError("n", lineStream);
				continue;
			}
		
			cout << "Modified: resistor " << name << " from " << old << " Ohms to " << resistance << " Ohms\n> ";
			cout.flush();
		}
	
		else if (cmd == "printR" || cmd == "deleteR") {		/* PRINTR & DELETER COMMANDS */
			lineStream >> name;
			line = CheckName(name, cmd, lineStream);
			if(line != "n")		continue;
	
			lineStream >> junk;
			line = CheckJunk(lineStream);
			if(line != "n")		continue;
			
			/* Finds resistor. If NULL, doesn't exist. (Doesn't check
				if the name entered was "all". */
			Resistor **resptr = nL->findRes(name);
			if((resptr == NULL) && (name != "all")) {
				cout << "Error: resistor " << name << " not found\n> ";
				cout.flush();
				line = RestartAfterError("n", lineStream);
				continue;
			}
		
			if(cmd == "printR") {
				cout << "Print:" << endl;
				(*resptr)->print();
				cout << "> ";
				cout.flush();
			}
			else {
				if(name == "all") {
					delete nL;
					nL = new NodeList;
					/* Allocating a new NodeList will automatically allocate
						the subclass structures within it. */
					cout << "Deleted: all resistors\n> ";
					cout.flush();
				}
				else {
					nL->deleteRes(name);
					cout << "Deleted: resistor " << name << "\n> ";
					cout.flush();
				}
			}
		}
	
		else if(cmd == "printNode") {		/* PRINTNODE COMMAND */
			int all = 1;
			string line2 = line;
			lineStream >> nodeA;
			line = CheckNode(nodeA, cmd, line, lineStream);
			if(line != "n" && line != "all")		continue;
			else if(line == "all")					all = 0; 	// used as a boolean
		
			string word;
			stringstream secondStream(line2);
			/* Need to create a new stringstream, feed in the original line that was entered,
				and then get rid of the first two arguments & check for extra arguments. */
			secondStream >> cmd;
			secondStream >> word;
			secondStream >> junk;
			line = CheckJunk(secondStream);
			if(line != "n")		continue;
			
			cout << "Print:" << endl;
			
			/* Prints all, or finds specific node and prints it. */
			if(all == 0) {
				nL->printAll();
			}
			else {
				Node **nodeptr = nL->findNode(nodeA);
				if(nodeptr == NULL) {
					cout << "Connections at node " << nodeA << ": " << "0 resistor(s)" << endl;
				}
				else (*nodeptr)->print();
			}
			cout << "> ";
			cout.flush();
		}
		
		else if(cmd == "setV") {		/* SETV COMMAND */
			lineStream >> nodeA;
			line = CheckNode(nodeA, cmd, line, lineStream);
			if(line != "n")		continue;
			
			lineStream >> voltage;
			line = CheckVoltage(voltage, lineStream);
			if(line != "n")		continue;
		
			lineStream >> junk;
			line = CheckJunk(lineStream);
			if(line != "n")		continue;
			
			/* Sets voltage and uses boolean value "true" to tell the node
				that the voltage was set by the user. */
			nL->setOrUnset(nodeA, voltage, true);
			
			cout << "Set: node " << nodeA << " to " << voltage << " Volts\n> ";
			cout.flush();
		}
		
		else if(cmd == "unsetV") {		/* UNSETV COMMAND */
			lineStream >> nodeA;
			line = CheckNode(nodeA, cmd, line, lineStream);
			if(line != "n")		continue;
		
			lineStream >> junk;
			line = CheckJunk(lineStream);
			if(line != "n")		continue;
			
			/* Unsets voltage (back to 0) and uses the boolean value "false"
				to tell the node that the voltage should be determined by "solve." */			
			nL->setOrUnset(nodeA, 0, false);
			
			cout << "Unset: the solver will determine the voltage of node " << nodeA << " \n> ";
			cout.flush();
		}
		
		else if(cmd == "solve") {		/* SOLVE COMMAND */
			/* If solve returns false, then no nodes have set voltages. */
			if(!(nL->solve())) {
				cout << "Error: no nodes have their voltage set\n> ";
				cout.flush();
				line = RestartAfterError("n", lineStream);
				continue;
			}
			cout << "> ";
			cout.flush();
		}
	
		else {		/* If none of the commands match... */
			line = RestartAfterError("invalid command", lineStream);
			continue;
		}
		
		line = RestartAfterError("n", lineStream);
		/* Restart everything and take in another line, except
			don't print an error message (which is why I put in "n" as the parameter) */
	}
	
	delete nL;
	/* After deleting the node list, the destructors delete the nodes,
		resistor lists, and resistors within that node list. */
	return 0;
}
