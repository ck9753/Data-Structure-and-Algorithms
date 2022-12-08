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
  //std::map<std::string, long int> combinedMap;

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
  //void runStoryBook_s4(const char * dir);  // for step 4
  void checkValidity();
  //void checkValidity_s4();  // for step 4
  bool checkUserChoice(size_t userChoice, size_t presentPageNum);
  //bool checkUserChoice_s4(size_t userChoice, size_t presentPageNum);  // for step 4
  //void printChoiceOptions(Page inputPage);                            // for step 4
  void processPages();
  //void processPages_s4();  // for step 4
  std::vector<Page> dfs(Page start, Page end);
  void printCurrentPath(std::vector<Page> currentPath);
  void findWaysToWin();
  //void storeToCombinedMap(Page userChoicePage);  // for step 4
};

class storyBook_s4 {
 public:
  std::vector<std::pair<size_t, Page_s4> > pages;
  std::map<std::string, long int> combinedMap;

  void runStoryBook(const char * dir);
  void checkValidity();
  bool checkUserChoice(size_t userChoice, size_t presentPageNum);
  void printChoiceOptions(Page_s4 inputPage);  // for step 4
  void processPages();
  //std::vector<Page> dfs(Page start, Page end);
  //void printCurrentPath(std::vector<Page> currentPath);
  //void findWaysToWin();
  void storeToCombinedMap(Page_s4 userChoicePage);  // for step 4
};
