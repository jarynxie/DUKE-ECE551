#ifndef __SHELL_H__
#define __SHELL_H__

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
  //Use a private map to store all the variables
  map<string, string> varMap;

 public:
  Shell(){};
  //Initialize ECE551PATH and store all variables in the map
  void initVar(void);
  //Set the cariable accordingly.
  void setVar(string & inputStr);
  //Export the variable accordingly.
  void exportVar(string & inputStr);
  //Reverse the variable accordingly.
  void revVar(string & inputStr);
  //Support "env", which prints all the variables
  void printEnv(void);
  //Return the variable map
  map<string, string> getVarMap(void);
  ~Shell(){};
};

//This method initializes ECE551PATH with PATH and store all the variables in the map
void Shell::initVar(void) {
  //get value of PATH to initialize ECE551PATH
  string path = string(getenv("PATH"));
  //insert ECE551PATH into the map
  varMap.insert(pair<string, string>("ECE551PATH", path));
  //set ECE551PATH
  setenv("ECE551PATH", getenv("PATH"), 1);
  for (int i = 0; environ[i] != NULL; i++) {
    string var = string(environ[i]);
    //get the name of var
    string name = var.substr(0, var.find('='));
    //get the value of var
    string value = var.substr(var.find('=') + 1, var.length() - 1);
    //insert var into map
    varMap[name] = value;
  }
}

//This method parse the input and set the variable accordingly
void Shell::setVar(string & inputStr) {
  //Check if the commad starts with "set"
  if (inputStr.substr(0, 4) != "set ") {
    cout << "Usage: set var value" << endl;
    return;
  }
  //Parse the input to get the string which contains variable name and it's value
  string varnValue = inputStr.substr(4, inputStr.length() - 1);
  //Find the ' '
  size_t deli = varnValue.find(' ');
  //Parse the variable name
  string var = varnValue.substr(0, deli);
  //Check if the variable name is valid
  for (size_t i = 0; i < var.length(); i++) {
    if (isdigit(var[i]) || isalpha(var[i]) || var[i] == '_') {
      continue;
    }
    else {
      cout << "Invalid variable name!" << endl;
      return;
    }
  }
  //PArse the variable's value.
  string value = varnValue.substr(deli + 1, varnValue.length() - 1);
  //If user tries to change ECE551PATH, automically export it.
  if (var == "ECE551PATH") {
    int setResult = setenv("ECE551PATH", (char *)value.c_str(), 1);
    if (setResult == -1) {
      cout << "Unable to change ECE551PATH!" << endl;
    }
    else {
      cout << "Trying to change ECE551PATH, automically export it.Run env to check."
           << endl;
    }
  }
  //Check if the variable already exists. If so, just change it's value
  if (varMap.find(var) != varMap.end()) {
    varMap.find(var)->second = value;
    return;
  }
  //If not exist, insert it into the map, but not put in the real environment
  varMap.insert(pair<string, string>(var, value));
}

//This method parse the input and export the according variable
//Note: As stated on Piazza, I can choose if to automically export the variable that's already been exported before. Here, I choose that the user must EXPORT IT AGAIN after changing the variable's value, except that the user is trying to change "ECE551PATH".
void Shell::exportVar(string & inputStr) {
  //assert(inputStr.find("export") != string::npos);
  if (inputStr.substr(0, 7) != "export ") {
    cout << "Usage: export var" << endl;
    return;
  }
  //Parse the variable's name according to the input string
  string varName = inputStr.substr(7, inputStr.length() - 1);
  //Check if this variable exists in the map, if not, it cannot be exported
  map<string, string>::iterator it = varMap.find(varName);
  if (it == varMap.end()) {
    cout << "Variable not found!" << endl;
    return;
  }
  //Create char * type's variable name and value
  const char * name = it->first.c_str();
  const char * value = it->second.c_str();
  //Put this variable in the environment, "1" to indicate overwritten is enabled
  int setResult = setenv(name, value, 1);
  //Check if setenv is successfult. If not, report error
  if (setResult == -1) {
    cout << "Failed to export variable!" << endl;
    return;
  }
}

//This method parse the input string and reverse the accorind variable
void Shell::revVar(string & inputStr) {
  //Check if the input starts with "rev"
  if (inputStr.substr(0, 4) != "rev ") {
    cout << "Usage: rev var" << endl;
    return;
  }
  //Parse the variable name according to the input
  string varName = inputStr.substr(4, inputStr.length() - 1);
  //Check if the variable exists in the map. If not, it cannot be reversed
  map<string, string>::iterator it = varMap.find(varName);
  if (it == varMap.end()) {
    cout << "Variable not found!" << endl;
    return;
  }
  //Reverse the value of variable
  reverse(it->second.begin(), it->second.end());
}

//This method is used to support "env", which prints all the variables
void Shell::printEnv() {
  for (int i = 0; environ[i] != NULL; i++) {
    cout << environ[i] << endl;
  }
}

//This method return the varMap of the current shell
map<string, string> Shell::getVarMap(void) {
  return varMap;
}

#endif
