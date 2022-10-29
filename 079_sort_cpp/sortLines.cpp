#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

void sort_a_file(std::istream & x) {
  std::string s;
  std::vector<std::string> line;

  while (getline(x, s)) {
    line.push_back(s);
  }

  if ((x.eof() != 1) && (x.good() != 1)) {
    std::cerr << "Error for reading lines" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::sort(line.begin(), line.end());

  std::vector<std::string>::iterator iter = line.begin();

  while (iter != line.end()) {
    std::cout << *iter << std::endl;
    ++iter;
  }
}

void sort_files(int argc, char ** argv) {
  for (int i = 1; i < argc; i++) {
    std::ifstream y(argv[i], std::ifstream::in);

    if (!y.is_open()) {
      std::cerr << "Failed to open File" << std::endl;
      exit(EXIT_FAILURE);
    }

    sort_a_file(y);
    y.close();
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    sort_a_file(std::cin);
  }

  if (argc > 1) {
    sort_files(argc, argv);
  }

  return EXIT_SUCCESS;
}
