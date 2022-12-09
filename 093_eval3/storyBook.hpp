#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "page.hpp"

// class storyBook for step 1, 2, and 3
class storyBook {
 public:
  std::vector<std::pair<size_t, Page> > pages;

 public:
  // default constructor
  storyBook() : pages() {}

  // copy constructor
  storyBook(const storyBook & rhs) : pages(rhs.pages) {}
  // An assignment operator
  storyBook & operator=(const storyBook & rhs) {
    if (this != &rhs) {
      pages = rhs.pages;
    }
    return *this;
  }

  // destructor
  ~storyBook() {}

  void runStoryBook(const char * dir);
  void checkValidity();
  bool checkUserChoice(size_t userChoice, size_t presentPageNum);
  void processPages();
  std::vector<Page> dfs(Page start, Page end);
  void printCurrentPath(std::vector<Page> currentPath);
  void findWaysToWin();
};

// class storyBook_s4 for step 4
class storyBook_s4 {
 public:
  std::vector<std::pair<size_t, Page_s4> > pages;
  std::map<std::string, long int> combinedMap;

  void runStoryBook(const char * dir);
  void checkValidity();
  bool checkUserChoice(size_t userChoice, size_t presentPageNum);
  std::vector<size_t> printChoiceOptions(Page_s4 inputPage);
  void checkVariables(Page_s4 currPage);
  void processPages();
  void storeToCombinedMap(Page_s4 userChoicePage);
};
