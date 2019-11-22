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
  while (true) {
    pid_t cPid, w;
    int wstatus;
    cout << "ffosh$ ";
    char * newargv[] = {NULL, NULL};
    char * newenviron[] = {NULL};
    char readCin[256];
    cin.getline(readCin, 256);
    if (strcmp(readCin, "exit") == 0 || strcmp(readCin, "") == 0) {
      exit(EXIT_SUCCESS);
    }
    newargv[0] = readCin;
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
        w = wait(&wstatus);
        if (w == -1) {
          perror("wait");
          exit(EXIT_FAILURE);
        }

        if (WIFEXITED(wstatus)) {
          printf("exited, status=%d\n", WEXITSTATUS(wstatus));
        }
        else if (WIFSIGNALED(wstatus)) {
          printf("killed by signal %d\n", WTERMSIG(wstatus));
        }
        else if (WIFSTOPPED(wstatus)) {
          printf("stopped by signal %d\n", WSTOPSIG(wstatus));
        }
        else if (WIFCONTINUED(wstatus)) {
          printf("continued\n");
        }
      } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
    }
  }
  return EXIT_SUCCESS;
}
