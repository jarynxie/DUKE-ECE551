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

void searchVector(string commandName,
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
int checkFiles(vector<string> & range) {
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

string getCmdName(string cinput, char * environ) {
  stringstream inStream(cinput);
  string cmdName;
  getline(inStream, cmdName, ' ');
  if (cmdName.find('/') != string::npos) {
    return cmdName;
  }
  vector<string> search;
  searchVector(cmdName, cinput, environ, search);
  int pathIndex = checkFiles(search);
  if (pathIndex == -1) {
    cout << "Command " << cmdName << " not found\n";
    return (char *)"";
  }
  return search[pathIndex];
}

void parseArg(string & wholeStr, char ** argResult) {
  vector<string> args;
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
        args.push_back(tempStr);
        tempStr.clear();
        inQuote = false;
        continue;
      }
      if (i == str.length() - 1) {
        cout << "unclosed quotation\n";
        exit(EXIT_FAILURE);
      }
    }
    else {
      if (str[i] == '"') {
        inQuote = true;
        continue;
      }
      if (str[i] == ' ') {
        if (!tempStr.empty()) {
          args.push_back(tempStr);
          tempStr.clear();
        }
        continue;
      }
    }
    tempStr.push_back(str[i]);
    if (i == str.length() - 1 && !tempStr.empty()) {
      args.push_back(tempStr);
    }
  }
  for (size_t j = 0; j < args.size(); j++) {
    argResult[1 + j] = (char *)args[j].c_str();
  }
}

int main(int argc, char * argv[]) {
  if (argc != 1) {
    cout << "Usage: ./ffosh\n";
    exit(EXIT_FAILURE);
  }
  char * newenviron[] = {NULL, NULL};
  newenviron[0] = getenv("PATH");
  while (true) {
    pid_t cPid, w;
    int wstatus;
    cout << "ffosh$ ";
    char * newargv[256] = {NULL};
    string resultStr;
    getline(cin, resultStr);
    if (resultStr == "exit") {
      exit(EXIT_SUCCESS);
    }
    if (resultStr == "") {
      continue;
    }
    vector<string> search;
    string commandName = getCmdName(resultStr, newenviron[0]);
    if (commandName == "") {
      continue;
    }
    cPid = fork();
    if (cPid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    }
    if (cPid == 0) {
      const char * filePath = commandName.c_str();
      newargv[0] = (char *)filePath;
      parseArg(resultStr, newargv);
      execve(newargv[0], newargv, newenviron);
      perror("execve");
      exit(EXIT_FAILURE);
    }
    else {
      do {
        w = waitpid(-1, &wstatus, 0);
        if (w == -1) {
          perror("wait");
          exit(EXIT_FAILURE);
        }

        if (WEXITSTATUS(wstatus) == 0) {
          cout << "Program was successful\n";
        }
        else if (WEXITSTATUS(wstatus) != 0) {
          cout << "Program failed with code " << WEXITSTATUS(wstatus) << endl;
        }
        else if (WIFSIGNALED(wstatus)) {
          cout << "Terminated by signal " << WTERMSIG(wstatus) << endl;
        }
      } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
    }
  }
  return EXIT_SUCCESS;
}
