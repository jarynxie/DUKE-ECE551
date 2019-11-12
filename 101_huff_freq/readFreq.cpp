#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  std::ifstream curStream(fname);
  if (!curStream) {
    perror("Cannot open file!");
    exit(EXIT_FAILURE);
  }
  uint64_t * ans = new uint64_t[257]();
  uint64_t toInt;
  char c;
  while (curStream.get(c)) {
    toInt = (unsigned char)c;
    ans[toInt]++;
  }
  ans[256] = 1;
  curStream.close();
  return ans;
}
