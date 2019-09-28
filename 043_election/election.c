#include "election.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//include any other headers you need here...

size_t calColonIndex(const char * line, size_t startPos, size_t endPos) {
  size_t returnIndex = 0;  //position of colon from start to end pos
  for (size_t i = startPos; i < endPos; i++) {
    if (*(line + i) == ':') {
      returnIndex = i;  //set returnIndex the pos of first encountered colon
      break;
    }
  }
  return returnIndex;
}

void checkFormat(size_t firstColon, size_t secondColon, size_t thirdColon) {
  if (firstColon > MAX_STATE_NAME_LENGTH) {
    fprintf(stderr, "State name is too long!\n");
    exit(EXIT_FAILURE);
  }
  if (secondColon == 0 || thirdColon != 0) {
    fprintf(stderr, "Improper format!\n");
    exit(EXIT_FAILURE);
  }
}

void checkDigit(char * line) {
  for (size_t i = 0; i < strlen(line); i++) {
    if (isdigit(line[i]) == 0) {
      fprintf(stderr, "Population or electoralVotes is not digit!\n");
      exit(EXIT_FAILURE);
    }
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
  checkFormat(firstColon, secondColon, thirdColon);
  //declare the string for population and votes
  char pop[secondColon - firstColon];
  char votes[length - secondColon];
  //assign name string from the input
  strncpy(ansState.name, line, firstColon);
  ansState.name[firstColon] = '\0';
  //assign population string from input
  strncpy(pop, line + firstColon + 1, secondColon - firstColon - 1);
  pop[secondColon - firstColon - 1] = '\0';
  checkDigit(pop);  //check if the population string is digit
  //assign vote string from input
  strncpy(votes, line + secondColon + 1, length - secondColon - 1);
  votes[length - secondColon - 1] = '\0';
  checkDigit(votes);  // check if the votes string is digit
  //transfer population and vote strings to integer
  int population = atoi(pop);
  unsigned int electoralVotes = atoi(votes);
  //assign the population and votes of the returned struct
  ansState.population = population;
  ansState.electoralVotes = electoralVotes;
  return ansState;
}

void checkCountVoteFormat(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  if (stateData == NULL) {
    fprintf(stderr, "Invalid * stateData\n");
    exit(EXIT_FAILURE);
  }
  if (voteCounts == NULL) {
    fprintf(stderr, "Invalid * voteCounts\n");
    exit(EXIT_FAILURE);
  }
  if (nStates < 0) {
    fprintf(stderr, "Invalid nStates\n");
    exit(EXIT_FAILURE);
  }
  //check if votecounts of a state exceeds its population or is less than 0
  for (size_t i = 0; i < nStates; i++) {
    if (voteCounts[i] > stateData[i].population || voteCounts[i] < 0) {
      fprintf(stderr, "Invalid voteCounts at %s\n", stateData[i].name);
      exit(EXIT_FAILURE);
    }
  }
}

unsigned int countElectoralVotes(state_t * stateData,
                                 uint64_t * voteCounts,
                                 size_t nStates) {
  checkCountVoteFormat(stateData, voteCounts, nStates);  //check the input first
  size_t totalCount = 0;  // variable for counting total votes
  for (size_t i = 0; i < nStates; i++) {
    if (voteCounts[i] / (double)stateData[i].population > 0.5) {
      totalCount += stateData[i].electoralVotes;
    }
  }
  return totalCount;
}
//calculate votes/population ratio of each state
double * calRatio(state_t * stateData,
                  uint64_t * voteCounts,
                  size_t nStates,
                  double * returnRatio) {
  for (size_t i = 0; i < nStates; i++) {
    returnRatio[i] = voteCounts[i] / (double)stateData[i].population;
  }
  return returnRatio;
}
//check each state if it needs a recount
void checkRecount(state_t * stateData, double * votesPopRatio, size_t nStates) {
  for (size_t i = 0; i < nStates; i++) {
    if (votesPopRatio[i] >= 0.495 && votesPopRatio[i] <= 0.505) {
      fprintf(stdout,
              "%s requires a recount (Candidate A has %.2f%% of the vote)\n",
              stateData[i].name,
              votesPopRatio[i] * 100);
    }
  }
}
void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  checkCountVoteFormat(stateData, voteCounts, nStates);  //check the input first
  double votesPopRatio[nStates];  //array to store the votes/population of each state
  calRatio(stateData, voteCounts, nStates, votesPopRatio);
  checkRecount(stateData, votesPopRatio, nStates);
}

size_t calLargestWin(double * votesPopRatio, size_t nStates) {
  size_t largestIndex = 0;
  for (size_t i = 1; i < nStates; i++) {
    if (votesPopRatio[i] > votesPopRatio[largestIndex]) {
      largestIndex = i;  //update largestIndex if the ration of current state is larger
    }
  }
  return largestIndex;
}
void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  checkCountVoteFormat(stateData, voteCounts, nStates);  //check the input first
  double votesPopRatio[nStates];  //array to store the votes/population of each state
  calRatio(stateData, voteCounts, nStates, votesPopRatio);
  size_t largestIndex = calLargestWin(votesPopRatio, nStates);
  fprintf(stdout,
          "Candidate A won %s with %.2f%% of the vote\n",
          stateData[largestIndex].name,
          votesPopRatio[largestIndex] * 100);
}
