#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t getEqualPos(const char * str) {
  size_t returnIndex = 0;
  for (size_t i = 0; i < strlen(str); i++) {
    if (*(str + i) == '=') {
      returnIndex = i;
      break;
    }
  }
  return returnIndex;
}
void stripNewLine(char * str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}

kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    return NULL;
  }
  kvarray_t * answer = malloc(sizeof(*answer));
  answer->kvpairs = NULL;
  answer->length = 0;
  char * curr = NULL;
  size_t sz;
  size_t firstEqual = 0;
  size_t i = 0;
  while (getline(&curr, &sz, f) >= 0) {
    answer->kvpairs = realloc(answer->kvpairs, (i + 1) * sizeof(*answer->kvpairs));
    answer->length++;
    answer->kvpairs[i] = NULL;
    answer->kvpairs[i] = malloc(sizeof(*answer->kvpairs[i]));
    //answer->kvpairs[i]->key = malloc(sizeof(*answer->kvpairs[i]->key));
    //answer->kvpairs[i]->value = malloc(sizeof(*answer->kvpairs[i]->value));
    stripNewLine(curr);
    firstEqual = getEqualPos(curr);
    answer->kvpairs[i]->key = strndup(curr, firstEqual);
    answer->kvpairs[i]->value = strdup(curr + firstEqual + 1);
    curr = NULL;
    i++;
  }
  free(curr);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    exit(EXIT_FAILURE);
  }
  return answer;
}

void freeKVs(kvarray_t * pairs) {
  for (int i = 0; i < pairs->length; i++) {
    free(pairs->kvpairs[i]->key);
    free(pairs->kvpairs[i]->value);
    free(pairs->kvpairs[i]);
  }
  free(pairs->kvpairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (int i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvpairs[i]->key, pairs->kvpairs[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (int i = 0; i < pairs->length; i++) {
    if (!strcmp(key, pairs->kvpairs[i]->key)) {
      return pairs->kvpairs[i]->value;
    }
  }
  return NULL;
}
