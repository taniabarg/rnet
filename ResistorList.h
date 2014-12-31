#ifndef RESISTORLIST_H
#define RESISTORLIST_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

#include "Resistor.h"

class ResistorList {
	private:
		Resistor *head;
	public:
		ResistorList();
		~ResistorList();
		Resistor *getHead();
		void insertRes(string name_, double resistance_, int endpointNodeIDs_[2]);
		Resistor **findResR(string name_);
		friend class NodeList;
};

#endif
