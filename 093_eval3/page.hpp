#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>

// Page class for step 1, 2, and 3
class Page {
 public:
  size_t pageNum;
  std::string pageType;                                  // W, L, or N
  std::vector<std::pair<size_t, std::string> > choices;  // <destNum, string>
  std::vector<std::string> storyInsidePage;
  //std::map<std::string, long int> variables;  // map for varialbes

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
  //void printPage_s4();  // for step 4
};

// readStory class for step 1, 2, and 3
class readStory {
 public:
  std::vector<std::string> allPageDeclaration;
  std::vector<std::string> allChoices;

  bool readStoryFile(const char * filename);
  //bool readStoryFile_s4(const char * filename);
  std::vector<std::string> readPageFile(const char * filename);
  void printPage(std::vector<std::string> pageText);
  std::vector<std::pair<size_t, Page> > storeParsedDataToPage(const char * argv1);
};

// Page_s4 class for step 4
class Page_s4 {
 public:
  size_t pageNum;
  std::string pageType;  // W, L, or N
  struct choices_s {
    size_t destNum;
    std::string text;
    std::map<std::string, long int> keyValue;
    std::string key;
    long int value;
  };
  std::vector<choices_s> choices;
  std::vector<std::string> storyInsidePage;
  std::map<std::string, long int> variables;  // map for variables

 public:
  void printPage();
};

// readStory_s4 class for step 4
class readStory_s4 {
 public:
  std::vector<std::string> allPageDeclaration;
  std::vector<std::string> allChoices;
  std::vector<std::string> allVariables;

  bool readStoryFile(const char * filename);
  std::vector<std::string> readPageFile(const char * filename);
  void printPage(std::vector<std::string> pageText);
  std::vector<std::pair<size_t, Page_s4> > storeParsedDataToPage(const char * argv1);
};
