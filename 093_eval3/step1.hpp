#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "page.hpp"

class readStory {
 public:
  std::vector<std::string> allPageDeclaration;
  std::vector<std::string> allChoices;

  //std::vector<std::pair<size_t, std::string> > allChoices;

  bool readStoryFile(const char * filename);
  std::vector<std::string> readPageFile(const char * filename);
  //  std::vector<std::pair<size_t, std::string> > convrtChoicesFormat();
  void printPage(std::vector<std::string> pageText);
  std::vector<Page> storeParsedDataToPage(const char * argv1);
};
