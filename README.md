rnet
====

- A program that stores resistors in a circuit
- Circuit is defined by nodes; each node is connected to one or more resistors and each resistor is connected to two nodes by its endpoints
- Voltages of certain nodes can be set (i.e., adding a DC voltage source)
- "Solve" command solves for the DC voltage at all given nodes
- Uses linked lists to store nodes and resistors
- All entered commands are parsed and checked for validity and error messages are printed in case of invalid commands

VALID COMMANDS:
insertR (name) (resistance) (firstnode) -> (secondnode)
modifyR (name) (resistance)
printR (name OR all)
printNode (nodeID OR all)
deleteR (name OR all)
setV (nodeID) (voltage)
unsetV (nodeID)
solve

COMPILE:
g++ -g -Wall -Werror -o rnet Node.cpp Resistor.cpp NodeList.cpp ResistorList.cpp Rparser.cpp Main.cpp
