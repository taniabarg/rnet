#ifndef RESISTOR_H
#define RESISTOR_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Resistor {
	private:
		double resistance;
		string name;
		int endpointNodeIDs[2];
		int rIndex;
		Resistor *next;
	public:
		Resistor();
		Resistor(int, string, double, int[2]);
		~Resistor();
		Resistor *getNext();
		string getName() const;
		double getResistance() const;
		int *getEndpoints();
		int getRIndex() const;
		void setResistance(double);
		void print();
		friend class ResistorList;
		friend class NodeList;
};

#endif
