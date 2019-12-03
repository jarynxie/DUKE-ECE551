#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
extern char ** environ;

using namespace std;
class Shell {
 private:
  map<string, string> varMap;

 public:
  Shell(){};
  void initPath(void);
  void setVar(string & inputStr);
  void exportVar(string & inputStr);
  void revVar(string & inputStr);
  void printEnv(void);
  map<string, string> getVarMap(void);
  ~Shell(){};
};

void Shell::initPath(void) {
  string path = string(getenv("PATH"));
  varMap.insert(pair<string, string>("ECE551PATH", path));
  setenv("ECE551PATH", getenv("PATH"), 1);
}
void Shell::setVar(string & inputStr) {
  if (inputStr.substr(0, 4) != "set ") {
    cout << "Usage: set var value" << endl;
    return;
  }
  string varnValue = inputStr.substr(4, inputStr.length() - 1);
  size_t deli = varnValue.find(' ');
  string var = varnValue.substr(0, deli);
  for (size_t i = 0; i < var.length(); i++) {
    if (isdigit(var[i]) || isalpha(var[i]) || var[i] == '_') {
      continue;
    }
    else {
      cout << "Invalid variable name!" << endl;
      return;
    }
  }
  string value = varnValue.substr(deli + 1, varnValue.length() - 1);

  //make_pair<string, string> varPair(var, value);

  if (varMap.find(var) != varMap.end()) {
    varMap.find(var)->second = value;
    return;
  }
  varMap.insert(pair<string, string>(var, value));
  //varMap.insert(varPair);
}

void Shell::exportVar(string & inputStr) {
  //assert(inputStr.find("export") != string::npos);
  if (inputStr.substr(0, 7) != "export ") {
    cout << "Usage: export var" << endl;
    return;
  }
  string varName = inputStr.substr(7, inputStr.length() - 1);
  map<string, string>::iterator it = varMap.find(varName);
  if (it == varMap.end()) {
    cout << "Variable not found!" << endl;
    return;
  }
  const char * name = it->first.c_str();
  const char * value = it->second.c_str();
  int setResult = setenv(name, value, 1);
  if (setResult == -1) {
    cout << "Failed to export variable!" << endl;
    return;
  }
};

void Shell::revVar(string & inputStr) {
  if (inputStr.substr(0, 4) != "rev ") {
    cout << "Usage: rev var" << endl;
    return;
  }
  string varName = inputStr.substr(4, inputStr.length() - 1);
  map<string, string>::iterator it = varMap.find(varName);
  if (it == varMap.end()) {
    cout << "Variable not found!" << endl;
    return;
  }
  reverse(it->second.begin(), it->second.end());
};

void Shell::printEnv() {
  for (int i = 0; environ[i] != NULL; i++) {
    cout << environ[i] << endl;
  }
}

map<string, string> Shell::getVarMap(void) {
  return varMap;
}
