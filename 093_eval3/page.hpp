#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

class Page {
 public:
  size_t pageNum;
  std::string pageType;                                  // W, L, or N
  std::vector<std::pair<size_t, std::string> > choices;  // <destNum, string>
  std::vector<std::string> storyInsidePage;

 public:
  // Default constructor
  Page() : pageNum(0), pageType("N"), choices(), storyInsidePage() {}

  // A copy constructor
  Page(const Page & rhs) :
      pageNum(rhs.pageNum),
      pageType(rhs.pageType),
      choices(rhs.choices),
      storyInsidePage(rhs.storyInsidePage) {}

  // An assignment operator
  // performs a deep copy
  Page & operator=(const Page & rhs) {
    if (this != &rhs) {
      pageNum = rhs.pageNum;
      pageType = rhs.pageType;
      choices = rhs.choices;
      storyInsidePage = rhs.storyInsidePage;
    }
    return *this;
  }

  // Destructor
  // release any allocated memory
  ~Page(){};

  void printPage();
};

class readStory {
 public:
  std::vector<std::string> allPageDeclaration;
  std::vector<std::string> allChoices;

  bool readStoryFile(const char * filename);
  std::vector<std::string> readPageFile(const char * filename);
  void printPage(std::vector<std::string> pageText);
  std::vector<std::pair<size_t, Page> > storeParsedDataToPage(const char * argv1);
};
