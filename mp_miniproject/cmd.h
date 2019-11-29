#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
class Command {
 private:
  string cmdName;
  vector<string> argVector;
  void searchVector(string commandName,
                    string cinRead,
                    char * environ,
                    vector<string> & search);
  int checkFiles(vector<string> & range);

 public:
  /*
  Command() : cmdName(NULL) {
    for (size_t i = 0; i < 256; i++) {
      argVector[i] = NULL;
    }
  }
  */
  char * getCmdName() { return (char *)cmdName.c_str(); }
  void parseCmdName(string cinput, char * environ);
  void parseArg(string wholeStr);
  void execute(string inputStr, char ** newenviron);
};

void Command::parseCmdName(string cinput, char * environ) {
  stringstream inStream(cinput);
  string tempName;
  getline(inStream, tempName, ' ');
  if (tempName.find('/') != string::npos) {
    cmdName = tempName;
    argVector.push_back(tempName);
    return;
  }
  vector<string> search;
  searchVector(tempName, cinput, environ, search);
  int pathIndex = checkFiles(search);
  if (pathIndex == -1) {
    cout << "Command " << tempName << " not found\n";
    cmdName = "";
    //exit(EXIT_FAILURE);
    return;
  }
  cmdName = search[pathIndex];
  argVector.push_back(cmdName);
}

void Command::parseArg(string wholeStr) {
  string tempStr;
  if (wholeStr.find(' ') == string::npos) {
    return;
  }
  string str = wholeStr.substr(wholeStr.find(' ') + 1, wholeStr.length() - 1);
  bool inQuote = false;

  for (size_t i = 0; i < str.length(); i++) {
    if (i > 0 && str[i] == '\\' && str[i - 1] == '\\') {
      continue;
    }

    if (i > 0 && str[i] == '"' && str[i - 1] == '\\' && str[i - 2] != '\\') {
      tempStr[tempStr.length() - 1] = '"';
      continue;
    }

    if (inQuote) {
      if (str[i] == '"') {
        argVector.push_back(tempStr);
        tempStr.clear();
        inQuote = false;
        continue;
      }
      if (i == str.length() - 1) {
        cout << "Unclosed quotation!\n";
        //exit(EXIT_FAILURE);
        return;
      }
    }
    else {
      if (str[i] == '"') {
        inQuote = true;
        continue;
      }
      if (str[i] == ' ') {
        if (!tempStr.empty()) {
          argVector.push_back(tempStr);
          tempStr.clear();
        }
        continue;
      }
    }
    tempStr.push_back(str[i]);
    if (i == str.length() - 1 && !tempStr.empty()) {
      argVector.push_back(tempStr);
    }
  }
}

void Command::execute(string inputStr, char ** newenviron) {
  parseArg(inputStr);
  char * tempArgv[256] = {NULL};
  vector<string>::iterator it = argVector.begin();
  size_t index = 0;
  while (it != argVector.end()) {
    tempArgv[index] = (char *)it->c_str();
    index++;
    it++;
  }

  execve(tempArgv[0], tempArgv, newenviron);
  perror("execve");
  exit(EXIT_FAILURE);
}

void Command::searchVector(string commandName,
                           string cinRead,
                           char * environ,
                           vector<string> & search) {
  string envString(environ);
  stringstream envStream(envString);
  stringstream cinStream(cinRead);
  string temp;
  while (getline(envStream, temp, ':')) {
    search.push_back(temp);
  }
  vector<string>::iterator it = search.begin();
  while (it != search.end()) {
    it->push_back('/');
    it->append(commandName);
    it++;
  }
}

int Command::checkFiles(vector<string> & range) {
  vector<string>::iterator it = range.begin();
  int result = 0;
  while (it != range.end()) {
    const char * tempPath = it->c_str();
    if (!access(tempPath, F_OK)) {
      return result;
    }
    result++;
    it++;
  }
  return -1;
}
