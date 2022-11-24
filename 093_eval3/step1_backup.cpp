#include "step1.hpp"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/*
void Page::getPageNum(std::vector<std::string> pageDec) {
  std::vector<std::string>::iterator it = pageDec.begin();

  while (it != pageDec.end()) {
    size_t atIndex = (*it).find('@');
    std::string tmp_pageNum;
    if (atIndex == std::string::npos) {
      std::cerr << "@ doesn't exist. Incorrect template" << std::endl;
      exit(EXIT_FAILURE);
    }

    else if (atIndex != std::string::npos) {
      tmp_pageNum = (*it).substr(--atIndex);
      pageNum.push_back(atoi(tmp_pageNum.c_str()));
    }
  }
}
*/

bool Page::readFile(const char * fileName) {
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
    fullText.push_back(tmp_line.c_str());
  }

  // iterate each line
  std::vector<std::string>::iterator it = fullText.begin();
  // vector for page declarations
  std::vector<std::string> allPageDeclaration;

  // vector for choices of pages
  std::vector<std::pair<size_t, std::string> > allChoices;

  while (it != fullText.end()) {
    size_t atIndex = (*it).find('@');
    if (atIndex != std::string::npos) {
      allPageDeclaration.push_back(*it);
    }

    else {
      size_t firstColon = (*it).find(':');
      size_t secondColon = (*it).find_last_of(':');
      size_t page_num;
      std::string text;
      page_num = atoi(((*it).substr(--firstColon, 1)).c_str());
      text = (*it).substr(secondColon);

      allChoices.push_back(std::make_pair(page_num, text));
    }

    ++it;
  }
  parsePageDec(allPageDeclaration);
  file.close();
  return true;
}

void Page::parsePageDec(std::vector<std::string> pageDec) {
  std::vector<std::string>::iterator it = pageDec.begin();
  std::vector<std::string> textNames;

  while (it != pageDec.end()) {
    int atIndex = (*it).find('@');
    int coIndex = (*it).find(':');

    std::string tmp_pageNum;
    std::string tmp_pageType;
    std::string tmp_currentPageTextName;
    if (atIndex == -1) {
      std::cerr << "@ doesn't exist. Incorrect template" << std::endl;
      exit(EXIT_FAILURE);
    }

    else {
      // store pageNum
      tmp_pageNum = (*it).substr(--atIndex, 1);
      pageNum.push_back(atoi(tmp_pageNum.c_str()));

      // store pageType
      tmp_pageType = (*it).substr(atIndex, 1);
      pageType.push_back(tmp_pageType);

      // store currentPageTextName
      tmp_currentPageTextName = (*it).substr(++coIndex);
      textNames.push_back(tmp_currentPageTextName);
    }
  }
  getTextOfPages(textNames);
}

void
