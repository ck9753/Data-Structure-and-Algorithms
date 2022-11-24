#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

class Page {
 public:
  std::vector<size_t> pageNum;
  std::vector<std::string> pageType;
  std::vector<std::pair<size_t, std::string> > choices;  // <pageNum, string>
  std::vector<std::string> textOfPages;
  // vector for page declarations (might need to be deleted)
  //std::vector<std::string> pageDec;

  // read the page declaration file
  bool readFile(const char * filename);
  // split line by line
  void getEachLine(std::vector<std::string> _vector);

  // parse page declaration
  void parsePageDec(std::vector<std::string> pageDec);

  // get Text of Each Pages
  void getTextOfPages(std::vector<std::string> textNames);

  // get pageNum
  //void getPageNum(std::vector<std::string> pageDec);

  // get pageType
  //void getPageType(std::vector<std::string> pageDec);
  // read the each page file
  bool readPageFile(const char * filename);
};

class choicesOfPage {
  size_t pageNum;
  std::pair<size_t, std::string> choice;

  // read the page declaration file only
  bool readPageDecFile(const char * filename);
};
/*
  class Page {
   public:
    size_t pageNumber;
    size_t typeFlag;                        // 0 for L, 1 for W, 2 for N
    std::pair<int, std::string> next_page;  // <nextAddress, textForNext>
    std::vector<std::string> textOfPage;
    bool readFile(const char * file);
  };
*/
