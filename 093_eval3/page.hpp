#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

class Page {
 public:
  size_t pageNum;
  std::string pageType;                                  // W, L, or N
  std::vector<std::pair<size_t, std::string> > choices;  // <destNum, string>
  std::vector<std::string> textOfPages;

 public:
  // Default constructor
  Page() : pageNum(0), pageType("N"), choices(), textOfPages() {}
  //  Page(init_pageNum, init_pageType, init_choices, init_textOfPages) : page
  // A copy constructor
  Page(const Page & rhs) :
      pageNum(rhs.pageNum),
      pageType(rhs.pageType),
      choices(rhs.choices),
      textOfPages(rhs.textOfPages) {}

  // An assignment operator
  // performs a deep copy
  Page & operator=(const Page & rhs) {
    if (this != &rhs) {
      pageNum = rhs.pageNum;
      pageType = rhs.pageType;
      choices = rhs.choices;
      textOfPages = rhs.textOfPages;
    }
    return *this;
  }

  // Destructor
  // release any allocated memory
  ~Page(){};

  void printPage();  // start here
};

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
