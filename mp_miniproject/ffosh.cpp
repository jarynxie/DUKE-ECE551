#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;
int main(int argc, char * argv[]) {
  if (argc != 1) {
    cout << "Usage: ./ffosh\n";
    exit(EXIT_FAILURE);
  }
  char * newenviron[] = {NULL, NULL};
  newenviron[0] = getenv("PATH");
  //cout << newenviron[0];
  while (true) {
    pid_t cPid, w;
    int wstatus;
    cout << "ffosh$ ";
    char * newargv[] = {NULL, NULL};
    string readString;
    getline(cin, readString);
    char * readResult = new char[readString.length() + 1];
    strcpy(readResult, readString.c_str());
    if (strcmp(readResult, "exit") == 0) {
      exit(EXIT_SUCCESS);
    }
    if (strcmp(readResult, "") == 0) {
      continue;
    }
    newargv[0] = readResult;
    cPid = fork();
    if (cPid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    }
    if (cPid == 0) {
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
          printf("Program was successful\n");
        }
        else if (WEXITSTATUS(wstatus) != 0) {
          printf("Program failed with code %d\n", WEXITSTATUS(wstatus));
        }
        else if (WIFSIGNALED(wstatus)) {
          printf("Terminated by signal %d\n", WTERMSIG(wstatus));
        }
      } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
    }
  }
  return EXIT_SUCCESS;
}
