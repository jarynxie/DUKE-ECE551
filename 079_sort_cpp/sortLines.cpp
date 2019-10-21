#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

void sortnPrint(std::istream & stream) {
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(stream, line)) {
    lines.push_back(line);
  }
  std::sort(lines.begin(), lines.end());
  for (size_t i = 0; i < lines.size(); i++) {
    std::cout << lines[i] << std::endl;
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    sortnPrint(std::cin);
  }
  if (argc >= 1) {
    for (int i = 1; i < argc; i++) {
      std::ifstream input(argv[i]);
      sortnPrint(input);
    }
  }
  return EXIT_SUCCESS;
}
