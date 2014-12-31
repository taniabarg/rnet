#include "Node.h"

Node::Node() {
	next = NULL;
	rList = new ResistorList;
	voltage = 0;
	old_volt = 0;
	set = false;
}

Node::Node(int nodeID_) {
	next = NULL;
	nodeID = nodeID_;
	rList = new ResistorList;
	voltage = 0;
	old_volt = 0;
	set = false;
}

Node::~Node() {
	delete rList;
	delete next;
	next = NULL;
}

int Node::getNodeID() const {
	return nodeID;
}

ResistorList *Node::getrList() {
	return rList;
}

int Node::count() {
	int count_ = 0;
	for(Resistor *r = rList->getHead(); r != NULL; r = r->getNext()) {
		count_++;
	}
	return count_;
}

void Node::print() {
	int count_ = count();
	cout << "Connections at node " << nodeID << ": " << count_ << " resistor(s)" << endl;
	for(Resistor *r = rList->getHead(); r != NULL; r = r->getNext()) {
		cout << "  ";
		r->print();
	}
}

double Node::changeVolt(double voltage_) {
	old_volt = voltage;
	voltage = voltage_;
	double delta = old_volt - voltage;
	if(delta < 0)	delta = -delta;
	return delta;
}
