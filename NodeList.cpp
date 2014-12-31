#include "NodeList.h"

#define MIN_ITERATION_CHANGE 0.0001

using namespace std;

NodeList::NodeList() { head = NULL; }

NodeList::~NodeList() { delete head; head = NULL; }

Node **NodeList::findNode(int nodeID_) {
	Node **n;
	for(n = &head; (*n) != NULL; n = &((*n)->next)) {
		if((*n)->getNodeID() == nodeID_)
			return n;
	}
	return NULL; /* if not found, return NULL */
}

Node **NodeList::findOrInsert(int nodeID_) {
	/* find */
	Node **find;
	find = findNode(nodeID_);
	if(find != NULL)
		return find;
	/* sorted insert */
	Node **n;
	for(n = &head; (*n) != NULL && (nodeID_ > (*n)->nodeID); n = &((*n)->next));
	Node *ptr = new Node(nodeID_);
	ptr->next = (*n);
	*n = ptr;
	return n;
}

Resistor **NodeList::findRes(string name_) {
	Resistor **ptr;
	for(Node *n = head; n != NULL; n = n->next) {
		ptr = (n->getrList())->findResR(name_);
		if((*ptr) != NULL)	return ptr;
	}
	return NULL;
}

bool NodeList::modifyRes(string name_, double resistance_) {
	/* Note: There are two copies of resistors in every node list. */
	Resistor **ptr = findRes(name_);
	if(ptr == NULL)		return false;
	int nodeA = ((*ptr)->getEndpoints())[0];
	int nodeB = ((*ptr)->getEndpoints())[1];
	Node *n;
	/* Find first copy */
	for(n = head; n->nodeID != nodeA; n = n->next);
	Resistor **res1 = (n->getrList())->findResR(name_);
	(*res1)->setResistance(resistance_);
	/* Find second copy */
	for(n = head; n->nodeID != nodeB; n = n->next);
	Resistor **res2 = (n->getrList())->findResR(name_);
	(*res2)->setResistance(resistance_);
	return true;
}

bool NodeList::deleteRes(string name_) {
	/* delete first copy */
	Resistor **ptr1 = findRes(name_);
	if(ptr1 == NULL)		return false;
	Resistor *temp = *ptr1;
	*ptr1 = (*ptr1)->next;
	temp->next = NULL;
	delete temp;
	/* delete second copy */
	Resistor **ptr2 = findRes(name_);
	Resistor *temp2 = *ptr2;
	*ptr2 = (*ptr2)->next;
	temp2->next = NULL;
	delete temp2;
	return true;
}

void NodeList::printAll() {
	for(Node *n = head; n != NULL; n = n->next) {
		if(n->count() != 0)	n->print();
	}
}

void NodeList::setOrUnset(int nodeID, double voltage_, bool set_) {
	/* Boolean value indicates whether the voltage has been set by
		the user or not. */
	Node **ptr = findOrInsert(nodeID);
	(*ptr)->changeVolt(voltage_);
	(*ptr)->set = set_;
}

bool NodeList::checkValid() {
	/* If any of the voltages have been set, return true.
		Else, return false. Useful for solve function */
	for(Node *n = head; n != NULL; n = n->next) {
		if(n->set == true)	return true;
	}
	return false;
}

bool NodeList::solve() {
	if(!checkValid()) return false;
	/* The above returns false if none of the voltages
		have been set. */
	double delta = 100;
	int otherID;
	Node **otherNode;
	double othervolt;
	double term1;
	double term2;
	bool iterate = true;
	while(iterate) {
		iterate = false;
		for(Node *n = head; n != NULL; n = n->next) {
			if(n->set == false) {
				term1 = 0;
				term2 = 0;
				for(Resistor *r = (n->getrList())->head; r != NULL; r = r->next) {
					/* Finds ID of other node */
					otherID = r->endpointNodeIDs[0];
					if(otherID == n->nodeID) {
						otherID = r->endpointNodeIDs[1];
					}
					otherNode = findNode(otherID);
					othervolt = (*otherNode)->voltage;
					term1 += 1/(r->resistance); // Term 1 of the formula
					term2 += othervolt/r->resistance; // Term 2 of the formula
				}
				delta = n->changeVolt((1/term1) * term2);
				if(delta > MIN_ITERATION_CHANGE)
					iterate = true;
					/* If any of the voltages change by more than 0.001,
						then the loop must iterate again. */
			}
		}
	}
	printSolve();
	return true;
}

void NodeList::printSolve() {
	cout << "Solve:" << endl;
	for(Node *n = head; n != NULL; n = n->next) {
		cout << "  Node " << n->nodeID << ": " << n->voltage << " V" << endl;
	}
}
