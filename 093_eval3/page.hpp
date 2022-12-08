#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>

class Page {
 public:
  size_t pageNum;
  std::string pageType;                                  // W, L, or N
  std::vector<std::pair<size_t, std::string> > choices;  // <destNum, string>

  // choices for step 4
  /*struct choices_s {
    size_t destNum;
    std::string text;
    std::map<std::string, long int> keyValue;
    std::string key;
    long int value;
  };
  std::vector<choices_s> choices_s4;
  */
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

class readStory {
 public:
  std::vector<std::string> allPageDeclaration;
  std::vector<std::string> allChoices;
  //std::vector<std::string> allVariables;

  bool readStoryFile(const char * filename);
  //bool readStoryFile_s4(const char * filename);
  std::vector<std::string> readPageFile(const char * filename);
  void printPage(std::vector<std::string> pageText);
  std::vector<std::pair<size_t, Page> > storeParsedDataToPage(const char * argv1);
  //std::vector<std::pair<size_t, Page> > storeParsedDataToPage_s4(
  //const char * argv1);  // for step 4
};

class Page_s4 {
 public:
  size_t pageNum;
  std::string pageType;  // W, L, or N
  //std::vector<std::pair<size_t, std::string> > choices;  // <destNum, string>
  struct choices_s {
    size_t destNum;
    std::string text;
    std::map<std::string, long int> keyValue;
    std::string key;
    long int value;
  };
  std::vector<choices_s> choices;
  std::vector<std::string> storyInsidePage;
  std::map<std::string, long int> variables;  // hash table for variables

 public:
  void printPage();
};

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
