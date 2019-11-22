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

void readCin(const char *& result) {
  string resultStr;
  getline(cin, resultStr);
  result = resultStr.c_str();
}

void searchVector(const char *& cinRead, char *& environ, vector<string> & search) {
  string envString(environ);
  stringstream envStream(envString);
  stringstream cinStream(cinRead);
  string temp = "";
  while (!envStream.eof()) {
    getline(envStream, temp, ':');
    search.push_back(temp);
  }
  string fileName = "";
  getline(cinStream, fileName, ' ');
  if (fileName.find('/') == string::npos) {
    vector<string>::iterator it = search.begin();
    while (it != search.end()) {
      it->push_back('/');
      it->append(fileName);
      it++;
    }
  }
}

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
    const char * cinCharStar = "";
    readCin(cinCharStar);
    if (strcmp(cinCharStar, "exit") == 0) {
      exit(EXIT_SUCCESS);
    }
    if (strcmp(cinCharStar, "") == 0) {
      continue;
    }
    vector<string> search;
    searchVector(cinCharStar, newenviron[0], search);
    cPid = fork();
    if (cPid == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    }
    if (cPid == 0) {
      vector<string>::iterator it = search.begin();
      while (it != search.end()) {
        const char * temp = it->c_str();
        newargv[0] = (char *)temp;
        execve(newargv[0], newargv, newenviron);
        it++;
      }
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
