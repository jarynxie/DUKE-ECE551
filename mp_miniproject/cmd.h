#ifndef __CMD_H__
#define __CMD_H__
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;
class Command {
 private:
  string cmdName;
  //Private vector to store all the arguments
  vector<string> argVector;
  //Private helper method to creat the search vector to search the location of the command
  void searchVector(string & commandName,
                    string & cinRead,
                    char *& environ,
                    vector<string> & search);
  //Private helper method to return the location of the command in the search vector
  int checkFiles(vector<string> & range);
  //Private helper method to transfer arguments that contain cariable to its value
  void checkVar(map<string, string> & map);
  //Check if need redirection
  bool checkRedir(void);
  //Make redirection, return file descriptor of the open file
  int redir(void);

 public:
  Command(){};
  //Return the name of current command
  char * getCmdName() { return (char *)cmdName.c_str(); }
  //Parse the argument name  according to input string and push to argument vector
  void parseCmdName(string & cinput, char *& environ, map<string, string> & map);
  //Parse all the arguments  according to input string and push to argument vector
  void parseArg(string & wholeStr);
  //Execute the command
  void execute(string & inputStr, map<string, string> & map);
  ~Command(){};
};

//This method parses the name of the argument and push it as the first element in the vector
void Command::parseCmdName(string & cinput, char *& environ, map<string, string> & map) {
  stringstream inStream(cinput);
  string tempName;
  //Get the name of the command
  getline(inStream, tempName, ' ');
  //If it has '/', just push it to the vector
  if (tempName.find('/') != string::npos) {
    cmdName = tempName;
    argVector.push_back(tempName);
    return;
  }
  //If it starts with '$', check if it's a variable. If so, replace it with its value.
  if (tempName[0] == '$') {
    string tempStr = tempName.substr(1, tempName.length() - 1);
    if (map.find(tempStr) != map.end()) {
      tempName = map.find(tempStr)->second;
    }
  }
  vector<string> search;
  //The command doesn't contain '/' or a known variable, create the search vector to fill its path
  searchVector(tempName, cinput, environ, search);
  //Get the first location of the command in the search vector
  int pathIndex = checkFiles(search);
  //If command doesn't exist in the search range, report error
  if (pathIndex == -1) {
    cerr << "Command " << tempName << " not found\n";
    cmdName = "";
    return;
  }
  else {
    //If found, push the command into the vector as the first element
    cmdName = search[pathIndex];
    argVector.push_back(cmdName);
  }
}

//This method is to parse the arguments and push them to argvector
void Command::parseArg(string & wholeStr) {
  string tempStr;
  //Check if the input is valid
  if (wholeStr.find(' ') == string::npos) {
    return;
  }
  //Get the string of input that excludes the command name
  string str = wholeStr.substr(wholeStr.find(' ') + 1, wholeStr.length() - 1);
  //Set a bool to indicate if in quotation mark
  bool inQuote = false;
  for (size_t i = 0; i < str.length(); i++) {
    //If contains \\, skip the second '\'
    if (i > 0 && str[i] == '\\' && str[i - 1] == '\\') {
      //Check if reach the end
      if (i == str.length() - 1 && !tempStr.empty()) {
        argVector.push_back(tempStr);
      }
      continue;
    }
    //Handle \"
    if (i > 0 && str[i] == '"' && str[i - 1] == '\\' && str[i - 2] != '\\') {
      tempStr[tempStr.length() - 1] = '"';
      //Check if reach the end
      if (i == str.length() - 1 && !tempStr.empty()) {
        argVector.push_back(tempStr);
      }
      continue;
    }

    //Handle "\ "
    if (i > 0 && str[i] == ' ' && str[i - 1] == '\\') {
      tempStr[tempStr.length() - 1] = ' ';
      //Check if reach the end
      if (i == str.length() - 1 && !tempStr.empty()) {
        argVector.push_back(tempStr);
      }
      continue;
    }

    if (inQuote) {
      //If reach the end of quotation, add to argVector
      if (str[i] == '"') {
        argVector.push_back(tempStr);
        tempStr.clear();
        //Unmark the inQuote flag to indicate that it is now out of quotation
        inQuote = false;
        continue;
      }
      //If reaches the end of input but still don't see a closed quotation mark, report error
      if (i == str.length() - 1) {
        cerr << "Unclosed quotation!\n";
        return;
      }
    }
    else {
      //Detect if it is now in quotation
      if (str[i] == '"') {
        inQuote = true;
        continue;
      }
      //A space means a new argument, push the old one to argVector
      if (str[i] == ' ') {
        if (!tempStr.empty()) {
          argVector.push_back(tempStr);
          tempStr.clear();
        }
        continue;
      }
    }
    //Push the current valut to the back of string
    tempStr.push_back(str[i]);
    //If reach the end, push the last argument in argvector
    if (i == str.length() - 1 && !tempStr.empty()) {
      argVector.push_back(tempStr);
    }
  }
}

//This method is to execute the according command by the input
void Command::execute(string & inputStr, map<string, string> & map) {
  //Parse the arguments and replace variable's name with its value
  parseArg(inputStr);
  //Replace variable name with its value
  checkVar(map);
  char * tempArgv[256] = {NULL};
  vector<string>::iterator it = argVector.begin();
  vector<string>::iterator end = argVector.end();
  size_t index = 0;
  int ifRedir = checkRedir();
  //If need redirection, the last two arguments do not pass to the program
  if (ifRedir == true) {
    end = argVector.end() - 2;
  }
  //Create char * according to vector of strings
  while (it != end) {
    tempArgv[index] = (char *)it->c_str();
    index++;
    it++;
  }
  //Make redirection and close the opened file
  if (ifRedir == true) {
    int id = redir();
    if (id != -1) {
      close(id);
    }
  }
  //execute the program
  execve(tempArgv[0], tempArgv, environ);
  return;
}

//This method is to create the search range for the command name
void Command::searchVector(string & commandName,
                           string & cinRead,
                           char *& environ,
                           vector<string> & search) {
  string envString(environ);
  stringstream envStream(envString);
  stringstream cinStream(cinRead);
  string temp;
  //Separate different paths by ":"
  while (getline(envStream, temp, ':')) {
    search.push_back(temp);
  }
  vector<string>::iterator it = search.begin();
  //Create all the possible absolute paths
  while (it != search.end()) {
    it->push_back('/');
    it->append(commandName);
    it++;
  }
}

//This method search the input vector to see if the command exists and return the position of it
int Command::checkFiles(vector<string> & range) {
  vector<string>::iterator it = range.begin();
  int result = 0;
  while (it != range.end()) {
    const char * tempPath = it->c_str();
    //If successful, access returns 0 and save the result
    if (!access(tempPath, F_OK)) {
      return result;
    }
    //Otherwise, increment result until it reaches the end
    result++;
    it++;
  }
  //If fail to find the command, return -1
  return -1;
}

//This method check the arguments, if variable, replace with its value
//Note1: Try to search the longest possible variable name
//Note2: If variable abc = 123, ece$abcece should be replaced with ece123ece.
void Command::checkVar(map<string, string> & map) {
  vector<string>::iterator argIt = argVector.begin();
  argIt++;
  //For every argument in argVector
  while (argIt != argVector.end()) {
    string str = *argIt;
    stringstream ss(str);
    string temp;
    vector<string> search;
    //Use $ to separate the variables
    while (getline(ss, temp, '$')) {
      if (temp != "" && str[max((int)str.find(temp) - 1, 0)] == '$') {
        search.push_back(temp);
      }
    }
    vector<string>::iterator it = search.begin();
    while (it != search.end()) {
      //Search backwards to find the longest possible variable
      for (size_t i = 0; i < it->length(); i++) {
        size_t len = it->length();
        string temp = it->substr(0, len - i);
        //If found in the variable map
        if (map.find(temp) != map.end()) {
          string value = map.find(temp)->second;
          size_t pos = str.find(*it);
          //Replace this variable name with its value and leave everything else alone
          string before = str.substr(0, pos - 1);
          string after = str.substr(pos + temp.length(), str.length() - 1);
          str = before.append(value);
          str.append(after);
          //Store the new string back to argvector
          *argIt = str;
          break;
        }
      }
      it++;
    }
    argIt++;
  }
}

//Note: Only support simple redirection when the last argument is the filepath
bool Command::checkRedir(void) {
  //If too few arguments, it's not redirection
  if (argVector.size() < 3) {
    return false;
  }
  //Check the second to last argument
  vector<string>::iterator it = argVector.end() - 2;
  return (*it == "<" || *it == ">" || *it == "2>");
}

//This method do the redirection and return the file descriptor
int Command::redir(void) {
  //The last argument is the filepath
  vector<string>::iterator path = argVector.end() - 1;
  //Convert the path from string to const char * to pass to open
  const char * pathName = path->c_str();
  //Get the type of redirection, which is the second to last argument
  vector<string>::iterator type = argVector.end() - 2;
  int fileid = -1;
  //Open the file with the specified path
  if (*type == "<") {
    fileid = open(pathName, O_RDONLY, S_IRWXU);
  }
  else {
    fileid = open(pathName, O_RDWR | O_CREAT, S_IRWXU);
  }
  //If open returns -1, fail to open the file
  if (fileid == -1) {
    cerr << "Fail to open the specified file!" << endl;
  }
  //redirects standard input for the command
  else if (*type == "<") {
    dup2(fileid, 0);
  }
  //redirects standard output
  else if (*type == ">") {
    dup2(fileid, 1);
  }
  //redirects standard error
  else if (*type == "2>") {
    dup2(fileid, 2);
  }
  //Return the file descriptor to close the file later
  return fileid;
}
#endif
