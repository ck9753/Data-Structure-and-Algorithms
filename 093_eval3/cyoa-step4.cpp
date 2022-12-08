#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "storyBook.hpp"

int main(int argc, char * argv[]) {
  if (argc != 2) {
    std::cerr << "Wrong command format. Expected: ./cyoa-step2 story_directory"
              << std::endl;
    exit(EXIT_FAILURE);
  }

  storyBook_s4 storyBook;
  storyBook.runStoryBook(argv[1]);
  storyBook.processPages();
  return EXIT_SUCCESS;
}
