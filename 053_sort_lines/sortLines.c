#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void sortnPrint(FILE * f) {
  char ** lines = NULL;
  char * sortedData = NULL;
  size_t sz;
  size_t i = 0;
  while (getline(&sortedData, &sz, f) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = sortedData;
    sortedData = NULL;
    i++;
  }
  free(sortedData);
  sortData(lines, i);
  for (size_t count = 0; count < i; count++) {
    fprintf(stdout, "%s", lines[count]);
    free(lines[count]);
  }
  free(lines);
}

void handleFile(char ** argv, int i) {
  FILE * f = fopen(argv[i + 1], "r");
  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }
  sortnPrint(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    sortnPrint(stdin);
  }
  if (argc >= 1) {
    for (int i = 0; i < argc - 1; i++) {
      handleFile(argv, i);
    }
  }
  return EXIT_SUCCESS;
}
