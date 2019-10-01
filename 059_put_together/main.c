#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

void removeNewLine(char * str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}
counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Can't open countfile!");
    exit(EXIT_FAILURE);
  }
  counts_t * counts = createCounts();
  char * curr = NULL;
  size_t sz;
  while (getline(&curr, &sz, f) >= 0) {
    removeNewLine(curr);
    addCount(counts, lookupValue(kvPairs, curr));
  }
  free(curr);
  if (fclose(f) != 0) {
    fprintf(stderr, "Can't close countfile");
    exit(EXIT_FAILURE);
  }
  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc < 3) {
    fprintf(stderr, "At least two file!");
    exit(EXIT_FAILURE);
  }
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "Can't close file %d", i);
      exit(EXIT_FAILURE);
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }

  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
