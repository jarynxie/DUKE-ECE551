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

#include "cmd.h"
#include "shell.h"
void changeDir(string inputStr) {
  string dir = inputStr.substr(inputStr.find("cd ") + 3, inputStr.length() - 1);
  int result = chdir((char *)dir.c_str());
  if (result == -1) {
    cout << "Failed to change directory\n";
  }
}
using namespace std;
int main(int argc, char * argv[]) {
  if (argc != 1) {
    cout << "Usage: ./ffosh\n";
    exit(EXIT_FAILURE);
  }
  Shell cmdShell;
  char * newenviron[] = {NULL, NULL};
  //char * ECE551PATH = getenv("PATH");
  setenv("ECE551PATH", getenv("PATH"), 1);
  //newenviron[0] = getenv("PATH");
  while (true) {
    //newenviron[0] = getenv("ECE551PATH");
    pid_t cPid, w;
    int wstatus;
    Command currCmd;
    char * curDir = get_current_dir_name();
    cout << "ffosh:" << curDir << " $";
    free(curDir);
    string resultStr;
    getline(cin, resultStr);
    if (resultStr == "exit") {
      exit(EXIT_SUCCESS);
    }
    if (resultStr == "") {
      continue;
    }
    if (resultStr == "env") {
      cmdShell.printEnv();
      continue;
    }
    if (resultStr.find("cd") != string::npos) {
      changeDir(resultStr);
      continue;
    }
    if (resultStr.substr(0, 3) == "set") {
      cmdShell.setVar(resultStr);
      continue;
    }
    if (resultStr.substr(0, 6) == "export") {
      cmdShell.exportVar(resultStr);
      continue;
    }
    if (resultStr.substr(0, 3) == "rev") {
      cmdShell.revVar(resultStr);
      continue;
    }
    newenviron[0] = getenv("ECE551PATH");
    currCmd.parseCmdName(resultStr, newenviron[0]);
    if (strcmp(currCmd.getCmdName(), "") == 0) {
      continue;
    }
    cPid = fork();
    if (cPid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    }
    if (cPid == 0) {
      currCmd.execute(resultStr, newenviron);
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
