#ifndef NODELIST_H
#define NODELIST_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

#include "Node.h"

class NodeList {
	private:
		Node *head;
	public:
		NodeList();
		~NodeList();
		Node **findNode(int nodeID_);
		Node **findOrInsert(int nodeID_);
		Resistor **findRes(string name_);
		bool modifyRes(string name_, double resistance_);
		bool deleteRes(string name_);
		void printAll();
		void setOrUnset(int nodeID, double voltage_, bool set_);
		bool checkValid();
		bool solve();
		void printSolve();
};

#endif
