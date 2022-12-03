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

  storyBook storyBook;
  storyBook.runStoryBook(argv[1]);
  storyBook.findWaysToWin();

  //storyBook.processPages();

  return EXIT_SUCCESS;
}
