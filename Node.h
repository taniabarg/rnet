#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

#include "ResistorList.h"

class Node {
	private:
		ResistorList *rList;
		Node *next;
		int nodeID;
		double voltage;
		double old_volt;
		bool set;
	public:
		Node();
		Node(int nodeID_);
		~Node();
		ResistorList *getrList();
		int getNodeID() const;
		int count();
		void print();
		double changeVolt(double);
		friend class NodeList;
};

#endif

