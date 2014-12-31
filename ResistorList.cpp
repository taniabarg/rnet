#include "ResistorList.h"

ResistorList::ResistorList() { head = NULL; }

ResistorList::~ResistorList() { delete head; head = NULL; }

Resistor *ResistorList::getHead() { return head; }

void ResistorList::insertRes(string name_, double resistance_, int endpointNodeIDs_[2]) {
	Resistor **i = &head;
	int rIndex_ = 0;
	/* finds right place to put resistor */
	while((*i) != NULL) {
		i = &((*i)->next);
		rIndex_++;
	}
	*i = new Resistor(rIndex_, name_, resistance_, endpointNodeIDs_);
}

Resistor **ResistorList::findResR(string name_) {
	Resistor **p = &head;
	while(*p != NULL) {
		if((*p)->getName() == name_)
			break;
		p = &((*p)->next);
	}
	return p;
}
