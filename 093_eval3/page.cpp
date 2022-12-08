#include "page.hpp"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// A function that prints each page
void Page::printPage() {
  // print each line that is stored in textOfPages
  for (std::vector<std::string>::iterator it = storyInsidePage.begin();
       it != storyInsidePage.end();
       ++it) {
    std::cout << *it << std::endl;
  }

  // check if pageType is W, L, or N
  if (pageType == "W") {
    std::cout << "Congratulations! You have won. Hooray!" << std::endl;
  }

  else if (pageType == "L") {
    std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
  }

  else {
    std::cout << "What would you like to do?"
              << "\n"
              << std::endl;

    // a counter for choice index
    int k = 1;

    // print all choices
    for (std::vector<std::pair<size_t, std::string> >::iterator j = choices.begin();
         j != choices.end();
         ++j) {
      std::cout << " " << k << ". " << (*j).second << std::endl;
      k++;
    }
  }
}

// read story.txt file from input directory and split it by allpagedeclaration and allChoices
bool readStory::readStoryFile(const char * dir) {
  std::string storyTxt = "/story.txt";
  storyTxt = dir + storyTxt;

  const char * fileName = storyTxt.c_str();
  std::ifstream file;
  file.open(fileName);

  // check if the file can be opened
  if (file.fail()) {
    return false;
  }

  std::vector<std::string> fullText;
  // store each line of story.txt to fullText
  while (!file.eof()) {
    std::string tmp_line;
    std::getline(file, tmp_line);
    if (!tmp_line.empty()) {
      fullText.push_back(tmp_line.c_str());
    }
  }

  // iterate each line
  std::vector<std::string>::iterator it = fullText.begin();

  while (it != fullText.end()) {
    size_t atIndex = (*it).find('@');

    // store line in allPageDeclaration if the line has @
    if (atIndex != std::string::npos) {
      allPageDeclaration.push_back(*it);
    }

    // store line in allChoices if the line does not have @
    else {
      allChoices.push_back(*it);
    }

    ++it;
  }

  // close file
  file.close();

  return true;
}

// read and store each page file to vector fullText
std::vector<std::string> readStory::readPageFile(const char * filename) {
  std::ifstream file;
  file.open(filename);

  if (file.fail()) {
    std::cerr << "Page file cannot be opened" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::vector<std::string> fullText;

  while (!file.eof()) {
    std::string tmp_line;
    // read a line from file
    std::getline(file, tmp_line);
    // store each line's pointer
    fullText.push_back(tmp_line.c_str());
  }
  return fullText;
}

// print each page text
void readStory::printPage(std::vector<std::string> pageText) {
  std::vector<std::string>::iterator it = pageText.begin();

  while (it != pageText.end()) {
    std::cout << *it << std::endl;
    ++it;
  }
}

//from allPagedeclaration and allChoices vector, parse and store it to pages vector
std::vector<std::pair<size_t, Page> > readStory::storeParsedDataToPage(const char * dir) {
  // declare vector pages
  std::vector<std::pair<size_t, Page> > pages;
  // declare page
  Page page;

  // iterate allpagedeclaration
  for (std::vector<std::string>::iterator i = allPageDeclaration.begin();
       i != allPageDeclaration.end();
       ++i) {
    std::string storyInsidePageName;

    // find @ and : locations
    int atIndex = (*i).find('@');
    int colonIndex = (*i).find(':');

    // get pageNum from the start of the line to the place before @
    page.pageNum = atoi(((*i).substr(0, atIndex)).c_str());
    // get pageType
    page.pageType = (*i).substr(atIndex + 1, 1);

    // parse allPagedeclaration into storyInsidepageName and read storyInsidePage
    storyInsidePageName = (*i).substr(++colonIndex);
    storyInsidePageName = "/" + storyInsidePageName;
    page.storyInsidePage = readPageFile((dir + storyInsidePageName).c_str());
    for (std::vector<std::string>::iterator j = allChoices.begin(); j != allChoices.end();
         ++j) {
      size_t firstColon = (*j).find(':');
      size_t secondColon = (*j).find_last_of(':');
      size_t page_num;
      size_t dest_num;
      std::string choiceText;

      // parse allChoices into page_num, dest_num, and choicetext
      page_num = atoi(((*j).substr(0, firstColon)).c_str());
      dest_num =
          atoi(((*j).substr(firstColon + 1, secondColon - firstColon - 1)).c_str());
      choiceText = (*j).substr(secondColon + 1);

      // if the current page number of choice is same as page number, store a pair of dest_num and choiceText
      if (page_num == page.pageNum) {
        page.choices.push_back(std::make_pair(dest_num, choiceText));
      }
    }

    // add new added page number and page data to pages
    pages.push_back(std::make_pair(page.pageNum, page));

    // clear choices in page.choices for next page choices
    page.choices.clear();
  }
  return pages;
}

// A function that prints each file text without choices
void Page_s4::printPage() {
  // print each line that is stored in textOfPages
  for (std::vector<std::string>::iterator it = storyInsidePage.begin();
       it != storyInsidePage.end();
       ++it) {
    std::cout << *it << std::endl;
  }
}

// read story.txt file from input directory and split it by allpagedeclaration, allchoices, and allvariables
bool readStory_s4::readStoryFile(const char * dir) {
  std::string storyTxt = "/story.txt";
  storyTxt = dir + storyTxt;

  const char * fileName = storyTxt.c_str();
  std::ifstream file;
  file.open(fileName);

  // check if the file can be opened
  if (file.fail()) {
    return false;
  }

  std::vector<std::string> fullText;
  // store each line of story.txt to fullText
  while (!file.eof()) {
    std::string tmp_line;
    std::getline(file, tmp_line);
    if (!tmp_line.empty()) {
      fullText.push_back(tmp_line.c_str());
    }
  }

  // iterate each line
  std::vector<std::string>::iterator it = fullText.begin();

  while (it != fullText.end()) {
    size_t atIndex = (*it).find('@');
    size_t doIndex = (*it).find('$');

    // store line in allPageDeclaration if the line has @
    if (atIndex != std::string::npos) {
      allPageDeclaration.push_back(*it);
    }

    if (doIndex != std::string::npos) {
      allVariables.push_back(*it);
    }

    // store line in allChoices if the line does not have @
    else if (atIndex == std::string::npos && doIndex == std::string::npos) {
      allChoices.push_back(*it);
    }

    ++it;
  }

  // close file
  file.close();

  return true;
}

// read and store each page file to vector fullText
std::vector<std::string> readStory_s4::readPageFile(const char * filename) {
  std::ifstream file;
  file.open(filename);

  if (file.fail()) {
    std::cerr << "Page file cannot be opened" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::vector<std::string> fullText;

  while (!file.eof()) {
    std::string tmp_line;
    // read a line from file
    std::getline(file, tmp_line);
    // store each line's pointer
    fullText.push_back(tmp_line.c_str());
  }
  return fullText;
}

// print each page text
void readStory_s4::printPage(std::vector<std::string> pageText) {
  std::vector<std::string>::iterator it = pageText.begin();

  while (it != pageText.end()) {
    std::cout << *it << std::endl;
    ++it;
  }
}

// from allPagedeclaration, allChoices, and allVariables, parse and store it to page vector
std::vector<std::pair<size_t, Page_s4> > readStory_s4::storeParsedDataToPage(
    const char * dir) {
  // declare vector pages
  std::vector<std::pair<size_t, Page_s4> > pages;
  // declare page
  Page_s4 page;

  // iterate allpagedeclaration
  for (std::vector<std::string>::iterator i = allPageDeclaration.begin();
       i != allPageDeclaration.end();
       ++i) {
    std::string storyInsidePageName;
    //std::unordered_map<std::string, size_t> variables;

    // find @ and : locations
    int atIndex = (*i).find('@');
    int colonIndex = (*i).find(':');

    // get pageNum from the start of the line to the place before @
    page.pageNum = atoi(((*i).substr(0, atIndex)).c_str());
    // get pageType
    page.pageType = (*i).substr(atIndex + 1, 1);

    // parse allPagedeclaration into storyInsidepageName and read storyInsidePage
    storyInsidePageName = (*i).substr(++colonIndex);
    storyInsidePageName = "/" + storyInsidePageName;
    page.storyInsidePage = readPageFile((dir + storyInsidePageName).c_str());
    for (std::vector<std::string>::iterator j = allChoices.begin(); j != allChoices.end();
         ++j) {
      Page_s4::choices_s ch_s;
      size_t firstColon = (*j).find(':');
      size_t secondColon = (*j).find_last_of(':');
      size_t bracketIndex = (*j).find('[');
      size_t cldbracketIndex = (*j).find(']');
      size_t page_num;

      // conditional choices
      if (bracketIndex != std::string::npos) {
        size_t equalIndex = (*j).find('=');

        // parase allchoices into page_num, destNum, and choicetext
        page_num = atoi(((*j).substr(0, bracketIndex)).c_str());
        ch_s.destNum =
            atoi(((*j).substr(firstColon + 1, secondColon - firstColon - 1)).c_str());
        ch_s.key = (*j).substr(bracketIndex + 1, equalIndex - bracketIndex - 1);
        ch_s.value =
            atoi(((*j).substr(equalIndex + 1, cldbracketIndex - equalIndex - 1)).c_str());
        ch_s.keyValue[ch_s.key] = ch_s.value;
        ch_s.text = (*j).substr(secondColon + 1);
      }

      // normal choices
      else {
        // parse allChoices into page_num, dest_num, and choicetext
        page_num = atoi(((*j).substr(0, firstColon)).c_str());
        ch_s.destNum =
            atoi(((*j).substr(firstColon + 1, secondColon - firstColon - 1)).c_str());
        ch_s.text = (*j).substr(secondColon + 1);
        // store "empty" for key and -1 for value
        ch_s.key = "empty";
        ch_s.value = -1;
        ch_s.keyValue[ch_s.key] = ch_s.value;
      }

      // if the current page number of choice is same as page number, store a pair of dest_num and choiceText
      if (page_num == page.pageNum) {
        page.choices.push_back(ch_s);
      }
    }

    // add variable to hash table from allVariables
    for (std::vector<std::string>::iterator k = allVariables.begin();
         k != allVariables.end();
         k++) {
      size_t doIndex = (*k).find('$');
      size_t eqIndex = (*k).find('=');

      std::string key;
      long int value;

      size_t page_num = atoi(((*k).substr(0, doIndex)).c_str());
      if (page_num == page.pageNum) {
        key = (*k).substr(doIndex + 1, eqIndex - doIndex - 1);
        value = atoi(((*k).substr(eqIndex + 1)).c_str());
        page.variables[key] = value;
      }
    }

    // add new added page number and page data to pages
    pages.push_back(std::make_pair(page.pageNum, page));

    // clear choices in page.choices for next page choices
    page.choices.clear();
    page.variables.clear();
  }
  return pages;
}
