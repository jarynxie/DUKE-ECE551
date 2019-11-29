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

using namespace std;
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
    Command currCmd;
    cout << "ffosh$ ";
    string resultStr;
    getline(cin, resultStr);
    if (resultStr == "exit") {
      exit(EXIT_SUCCESS);
    }
    if (resultStr == "") {
      continue;
    }
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
