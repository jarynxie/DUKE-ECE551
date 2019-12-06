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

extern char ** environ;
// This function changes current directory, error will be reported if failed.
using namespace std;
void changeDir(string inputStr, map<string, string> map) {
  //Parse the input to get the directory
  string dir = inputStr.substr(inputStr.find("cd ") + 3, inputStr.length() - 1);
  //Check if need to do variable evaluation
  if (dir[0] == '$') {
    if (map.find(dir.substr(1, dir.length() - 1)) != map.end()) {
      dir = map.find(dir.substr(1, dir.length() - 1))->second;
    }
  }
  //Change the directory and give the result to "result"
  int result = chdir((char *)dir.c_str());
  //Check if it is successful or not
  if (result == -1) {
    cout << "Failed to change directory\n";
  }
}
using namespace std;
int main(int argc, char * argv[]) {
  //Check argc, if not currectly used, report the correct usage.
  if (argc != 1) {
    cout << "Usage: ./ffosh\n";
    exit(EXIT_FAILURE);
  }
  //Declare a shell object named cmdShell
  Shell cmdShell;
  //Initialize ECE551PATH and other variables
  cmdShell.initVar();
  while (true) {
    pid_t cPid, w;
    int wstatus;
    //Declare a Command object named "currCmd"
    Command currCmd;
    //Get the name of current directory
    char * curDir = get_current_dir_name();
    //Print the prompt
    cout << "ffosh:" << curDir << " $";
    //Free the char * returned by get_current_dir_name()
    free(curDir);
    string resultStr;
    //Get the variable map
    map<string, string> varMap = cmdShell.getVarMap();
    //If input encountered EOF, exist the shell
    while (!getline(cin, resultStr)) {
      cout << endl;
      exit(EXIT_SUCCESS);
    }
    //If type "exit", exit the shell
    if (resultStr.substr(0, 4) == "exit") {
      break;
    }
    //If the user type nothing, print a new prompt
    if (resultStr == "") {
      continue;
    }
    //After changing ECE551PATHIf, run "myenv" to see all the variables
    if (resultStr == "myenv") {
      cmdShell.printEnv();
      continue;
    }
    //If start with "cd", change the current directory accordingly
    if (resultStr.substr(0, 2) == "cd") {
      changeDir(resultStr, varMap);
      continue;
    }
    //If start with "set", set the vriable accordingly
    if (resultStr.substr(0, 3) == "set") {
      cmdShell.setVar(resultStr);
      continue;
    }
    //If start with "export", export the vriable accordingly
    if (resultStr.substr(0, 6) == "export") {
      cmdShell.exportVar(resultStr);
      continue;
    }
    ////If start with "rev", reverse the vriable accordingly
    if (resultStr.substr(0, 3) == "rev") {
      cmdShell.revVar(resultStr);
      continue;
    }
    //Get the value of "ECE551PATH", which has been initialized with initVar() before
    char * ece551p = getenv("ECE551PATH");
    //Parse the command name
    currCmd.parseCmdName(resultStr, ece551p, varMap);
    //If command name is empty, open a new prompt
    if (strcmp(currCmd.getCmdName(), "") == 0) {
      continue;
    }
    //Create a new child process
    cPid = fork();
    //Check if fork() is successful
    if (cPid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    }
    //If child process, execute the command
    if (cPid == 0) {
      currCmd.execute(resultStr, varMap);
      //If execve returns, exports error
      perror("execve");
      exit(EXIT_FAILURE);
    }
    else {
      w = waitpid(-1, &wstatus, 0);
      //Check if wait is successfull
      if (w == -1) {
        perror("wait");
        exit(EXIT_FAILURE);
      }
      //Report if the program runs successfully, report error otherwise
      if (WEXITSTATUS(wstatus) != 0) {
        cout << "Program failed with code " << WEXITSTATUS(wstatus) << endl;
      }
      else if (WIFSIGNALED(wstatus)) {
        cout << "Terminated by signal " << WTERMSIG(wstatus) << endl;
      }
      else {
        cout << "Program was successful\n";
      }
    }
  }
  return EXIT_SUCCESS;
}
