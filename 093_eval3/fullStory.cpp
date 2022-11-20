#include "fullStory.hpp"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

bool fullStory::readFile(const char * fileName) {
  std::ifstream file(fileName);

  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
    }
