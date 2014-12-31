#include "Resistor.h"

Resistor::Resistor() { rIndex = -1; next = NULL; }

Resistor::Resistor(int rIndex_, string name_, double resistance_, int endpoints_[2]) {
	rIndex = rIndex_;
	name = name_;
	resistance = resistance_;
	endpointNodeIDs[0] = endpoints_[0];
	endpointNodeIDs[1] = endpoints_[1];
	next = NULL;
}

Resistor::~Resistor() { delete next; next = NULL; }

Resistor *Resistor::getNext() { return next; }

string Resistor::getName() const {
	return name;
}

double Resistor::getResistance() const {
	return resistance;
}

int *Resistor::getEndpoints() {
	return endpointNodeIDs;
}

int Resistor::getRIndex() const {
	return rIndex;
}

void Resistor::setResistance(double resistance_) {
	resistance = resistance_;
}

void Resistor::print() {
	cout.setf(ios::fixed);
	cout.precision(2);
	cout << setw(20) << left << name << " " << setw(8) << right << resistance << " Ohms " << endpointNodeIDs[0] << " -> " << endpointNodeIDs[1] << endl;
}
