#include "counts.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  counts_t * answer = malloc(sizeof(*answer));
  assert(answer != NULL);
  answer->size = 0;
  answer->countUnknown = 0;
  answer->countArray = NULL;
  return answer;
}
void addCount(counts_t * c, const char * name) {
  if (name == NULL) {
    c->countUnknown++;
    return;
  }
  for (int i = 0; i < c->size; i++) {
    if (!strcmp(c->countArray[i]->name, name)) {
      c->countArray[i]->count++;
      return;
    }
  }
  c->countArray = realloc(c->countArray, (c->size + 1) * sizeof(*c->countArray));
  one_count_t * newName = malloc(sizeof(*newName));
  newName->name = strdup(name);
  newName->count = 1;
  c->countArray[c->size] = newName;
  c->size++;
}
void printCounts(counts_t * c, FILE * outFile) {
  for (int i = 0; i < c->size; i++) {
    fprintf(outFile, "%s: %d\n", c->countArray[i]->name, c->countArray[i]->count);
  }
  if (c->countUnknown != 0) {
    fprintf(outFile, "<unknown>: %d\n", c->countUnknown);
  }
}

void freeCounts(counts_t * c) {
  for (int i = 0; i < c->size; i++) {
    free(c->countArray[i]->name);
    free(c->countArray[i]);
  }
  free(c->countArray);
  free(c);
}
