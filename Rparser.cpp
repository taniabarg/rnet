#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include "Rparser.h"

using namespace std;

string RestartAfterError(string error, stringstream &stream) {
	/* When an error occurs, prints an error message (if necessary) and...
	 ...gets another line from cin, then continues the loop in "main". */
	stream.clear();
	stream.ignore(1000, '\n');
	if(error != "n") {
		cout << "Error: " << error << "\n> ";
		cout.flush();
	}
	string line;
	getline(cin, line);
	while(cin.fail() && !cin.eof()) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Error: failed to parse line\n> "; // ???
		continue;
	}
	return line;
}

/* The functions below check resistance names, resistance values, and node values (and extra arguments).
 	Each of these functions returns "n" if everything is okay - i.e. no errors occurred.
	Otherwise, it will return a line that is taken from cin by calling the above "RestartAfterError" function,
	and the main while loop will start over ("continue") when it sees that "n" was not returned.
	The line that WAS returned becomes the new input. */

string CheckResistance(double resistance, stringstream &stream) {
	// Checks if resistance value is valid.
	if(stream.fail()) {
		if(stream.eof())
			return RestartAfterError("too few arguments", stream); // resistance not entered
		else
			return RestartAfterError("invalid argument", stream); // not a double
	}
	else if(stream.peek() != ' ' && stream.peek() != '\n' && stream.peek() != '\r' && !stream.eof())
		return RestartAfterError("invalid argument", stream);	// invalid characters in resistance value
	else if(resistance < 0)
		return RestartAfterError("negative resistance", stream);	// negative resistance
	else return "n";
}

string CheckName(string name, string cmd, stringstream &stream) {
	// Checks if resistance name is valid.
	if(stream.fail())
		return RestartAfterError("too few arguments", stream);	// name not entered
	if((cmd == "modifyR" || cmd == "insertR") && name == "all")
		return RestartAfterError("resistor name cannot be the keyword \"all\"", stream); // "all" was entered
	else return "n";
}

string CheckNode(int node, string cmd, string line, stringstream &stream) {
	// Checks if node value is valid.
	if(stream.fail()) {
		if(stream.eof())
			return RestartAfterError("too few arguments", stream); // node value not entered
		else if(cmd == "printNode") {
			// SPECIAL CASE: in printNode, if whatever was entered was not an integer, lineStream...
			// ...will fail. I must check to see if this non-integer says "all".
			string not_an_int = "n";
			string extra;
			stringstream testStream; // create a new stringstream to see what the entered word was
			testStream << line;
			testStream >> extra;
			testStream >> not_an_int;
			if(not_an_int == "all")		return "all";	// "printNode all" was entered
			else return RestartAfterError("invalid argument", stream); // else, it was another invalid word (not "all")
		}
	}
	if(stream.peek() != ' ' && stream.peek() != '\n' && stream.peek() != '\r' && !stream.eof())
		return RestartAfterError("invalid argument", stream);	// invalid characters were entered
	return "n";
}

string CheckVoltage(double voltage, stringstream &stream) {
	if(stream.fail()) {
		if(stream.eof())
			return RestartAfterError("too few arguments", stream); // voltage not entered
		else
			return RestartAfterError("invalid argument", stream); // not a double
	}
	else if(stream.peek() != ' ' && stream.peek() != '\n' && stream.peek() != '\r' && !stream.eof())
		return RestartAfterError("invalid argument", stream);	// invalid characters in voltage value
	else return "n";
}

string CheckJunk(stringstream &stream) {
	// Checks if extra "junk" arguments were entered. (If not, the stream should fail.)
	if(!stream.fail())	return RestartAfterError("too many arguments", stream);
	else return "n";
}
