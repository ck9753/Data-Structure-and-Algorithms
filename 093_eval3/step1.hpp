#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

class readStory {
 public:
  std::vector<std::string> allPageDeclaration;
  std::vector<std::string> allChoices;

  //std::vector<std::pair<size_t, std::string> > allChoices;

  bool readStoryFile(const char * filenamee);
  std::vector<std::string> readPageFile(const char * filename);
  void printPage(std::vector<std::string> pageText);
};

class printStory {
 public:
  size_t pageNum_declar;
  size_t pageNum_choice;
  std::string pageType;
  std::string textOfThePageName;
  std::vector<std::string> pageText;

  void getPageNumAndType(std::string pageDeclaration, int atIndex, int colonIndex);
  void printOutput();
};

/*
class Page {
 public:
  size_t pageNum;
  std::string pageType;
  std::vector<std::string> choices;  // <pageNum, string>
  std::vector<std::string> textOfPages;

  // read the page declaration file
  //bool readFile(const char * filename);

  // parse page declaration
  //void parsePageDec(std::vector<std::string> pageDec);

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
*/
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
