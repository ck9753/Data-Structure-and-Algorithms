#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "page.hpp"

class storyBook {
 public:
  std::vector<std::pair<size_t, Page> > pages;

 public:
  // default constructor
  storyBook() : pages() {}

  // destructor
  ~storyBook() {}

  void runStoryBook(const char * dir);
  void checkValidities();
  //void processPages
};
