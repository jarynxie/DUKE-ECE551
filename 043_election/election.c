#include "election.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//include any other headers you need here...

size_t calColonIndex(const char * line, size_t startPos, size_t endPos) {
  size_t returnIndex = 0;
  for (size_t i = startPos; i < endPos; i++) {
    if (*(line + i) == ':') {
      returnIndex = i;
      break;
    }
  }
  return returnIndex;
}

void checkFormat(size_t secondColon, size_t thirdColon) {
  if (secondColon == 0 || thirdColon != 0) {
    fprintf(stderr, "Improper format!\n");
    exit(EXIT_FAILURE);
  }
}
state_t parseLine(const char * line) {
  state_t ansState;        //the return struct
  size_t firstColon = 0;   //variable for position of the first colon in the input string
  size_t secondColon = 0;  //variable for position of the second colon
  size_t thirdColon = 0;   //variable to check improper format (more than two colons)
  size_t length = strlen(line);  //length of input string
  //calculate the position of first colon
  firstColon = calColonIndex(line, 0, length);
  //calculate the position of the second colon
  secondColon = calColonIndex(line, firstColon + 1, length);
  //calculate the position of the third colon
  thirdColon = calColonIndex(line, secondColon + 1, length);
  //check if the input format is correct
  checkFormat(secondColon, thirdColon);
  //declare the string for population and votes
  char pop[secondColon - firstColon];
  char votes[length - secondColon];
  //assign name string from the input
  strncpy(ansState.name, line, firstColon);
  ansState.name[firstColon] = '\0';
  //assign population string from input
  strncpy(pop, line + firstColon + 1, secondColon - firstColon - 1);
  pop[secondColon - firstColon - 1] = '\0';
  //assign vote string from input
  strncpy(votes, line + secondColon + 1, length - secondColon - 1);
  votes[length - secondColon - 1] = '\0';
  //transfer population and vote strings to integer
  int population = atoi(pop);
  unsigned int electoralVotes = atoi(votes);
  //assign the population and votes of the returned struct
  ansState.population = population;
  ansState.electoralVotes = electoralVotes;
  return ansState;
}

unsigned int countElectoralVotes(state_t * stateData,
                                 uint64_t * voteCounts,
                                 size_t nStates) {
  //STEP 2: write me
  return 0;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
}
