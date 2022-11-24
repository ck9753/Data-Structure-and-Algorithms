#include "step1.hpp"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool readStory::readStoryFile(const char * fileName) {
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
  // vector for page declarations
  //std::vector<std::string> allPageDeclaration;

  // vector for choices of pages
  //std::vector<std::pair<size_t, std::string> > allChoices;

  while (it != fullText.end()) {
    size_t atIndex = (*it).find('@');

    //add how to handle blank line
    /*
    if ((*it).empty()) {
      break;
    }
    */

    if (atIndex != std::string::npos) {
      allPageDeclaration.push_back(*it);
    }

    else {
      size_t firstColon = (*it).find(':');
      size_t secondColon = (*it).find_last_of(':');
      size_t page_num;
      std::string text;
      page_num = atoi(((*it).substr(--firstColon, 1)).c_str());
      text = (*it).substr(++secondColon);

      allChoices.push_back(std::make_pair(page_num, text));
    }

    ++it;
  }
  file.close();

  return true;
}
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
    std::getline(file, tmp_line);
    // store each line's pointer
    fullText.push_back(tmp_line.c_str());
  }
  return fullText;
}

void readStory::printPage(std::vector<std::string> pageText) {
  std::vector<std::string>::iterator it = pageText.begin();

  while (it != pageText.end()) {
    std::cout << *it << std::endl;
    ++it;
  }
  //std::cout << "\n" << std::endl;
}

/*
void readStory::groupByPageNum(std::vector<std::string> allPageDeclaration,
                               std::vector<std::pair<size_t, std::string> > allChoices) {
  size_t pageNum_declar;
  size_t pageNum_choice;

  for (std::vector<std::string>::iterator i = allPageDeclaration.begin();
       i != allPageDeclaration.end();
       ++i) {
    int atIndex = (*i).find('@');
    pageNum_declar = atoi(((*i).substr(--atIndex, 1)).c_str());
    for (std::vector<std::pair<size_t, std::string> >::iterator j = allChoices.begin();
         j != allChoices.end();
         ++j) {
      //int colIndex = (*j).find(':');
      pageNum_choice = (j->first);  //atoi(((*j).substr(++colIndex).c_str));
      if (pageNum_choice == pageNum_declar) {
        infoByPageNum.push_back(std::make_pair(*i, j->second));
        //start from here
      }
    }
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
*/
