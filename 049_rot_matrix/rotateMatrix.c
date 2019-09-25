#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readMatrix(FILE * f, int matrix[][10]) {
  char tempString[12] = {0};
  for (int i = 0; i < 10; i++) {
    // fgets(tempString, 12, f);
    if (fgets(tempString, 12, f) != NULL) {
      if (strchr(tempString, '\n') != tempString + 10) {
        fprintf(stderr, "Improper input\n");
        exit(EXIT_FAILURE);
      }
      for (int j = 0; j < 10; j++) {
        matrix[i][j] = *(tempString + j);
      }
    }
  }
  if (fgetc(f) != EOF) {
    fprintf(stderr, "Improper input\n");
  }
}

void rotateMatrix(int matrix[][10]) {
  for (int i = 0; i < 5; i++) {
    for (int j = i; j < 9 - i; j++) {
      int temp = matrix[i][j];
      matrix[i][j] = matrix[9 - j][i];
      matrix[9 - j][i] = matrix[9 - i][9 - j];
      matrix[9 - i][9 - j] = matrix[j][9 - i];
      matrix[j][9 - i] = temp;
    }
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: inputFileName\n");
    return EXIT_FAILURE;
  }

  int matrix[10][10];
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      matrix[i][j] = 0;
    }
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open file");
    return EXIT_FAILURE;
  }

  readMatrix(f, matrix);
  rotateMatrix(matrix);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }

  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file!");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
