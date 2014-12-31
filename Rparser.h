/* PARSER PROTOTYPES */

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

string RestartAfterError(string error, stringstream &stream);
string CheckResistance(double resistance, stringstream &stream);
string CheckName(string name, string cmd, stringstream &stream);
string CheckNode(int node, string cmd, string line, stringstream &stream);
string CheckVoltage(double voltage, stringstream &stream);
string CheckJunk(stringstream &stream);
