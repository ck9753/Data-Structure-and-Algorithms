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
