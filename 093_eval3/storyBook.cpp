#include "storyBook.hpp"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// from readStory class, store pages vector to pages in storyBook class
void storyBook::runStoryBook(const char * argv1) {
  readStory file;
  pages = file.storeParsedDataToPage(argv1);
}
