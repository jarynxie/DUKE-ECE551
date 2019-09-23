#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int arrayMax(size_t * array, int n) {
  int largest = 0;
  for (int i = 0; i < n; i++) {
    if (array[i] > array[largest]) {
      largest = i;
    }
  }
  return largest;
}

void decrypt(FILE * f, size_t array[]) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      array[tolower(c) - 97]++;
    }
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: inputFileName\n");
    return EXIT_FAILURE;
  }
  size_t frequencyArray[26] = {0};
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open file");
    return EXIT_FAILURE;
  }
  decrypt(f, frequencyArray);
  int largest = arrayMax(frequencyArray, 26);
  int answer = largest + 97;
  int key = answer - 'e';
  printf("%d\n", key % 26);
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
