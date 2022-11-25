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

  while (it != fullText.end()) {
    size_t atIndex = (*it).find('@');

    if (atIndex != std::string::npos) {
      allPageDeclaration.push_back(*it);
    }

    else {
      allChoices.push_back(*it);
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
}

std::vector<Page> readStory::storeParsedDataToPage(const char * argv1) {
  std::vector<Page> pages;
  Page page;
  for (std::vector<std::string>::iterator i = allPageDeclaration.begin();
       i != allPageDeclaration.end();
       ++i) {
    std::string textOfPageName;
    int atIndex = (*i).find('@');
    int colonIndex = (*i).find(':');

    if (atIndex == 1) {
      page.pageNum = atoi(((*i).substr(atIndex - 1, 1)).c_str());
    }

    else if (atIndex == 2) {
      page.pageNum = atoi(((*i).substr(atIndex - 2, 2)).c_str());
    }

    page.pageType = (*i).substr(atIndex + 1, 1);
    textOfPageName = (*i).substr(++colonIndex);
    textOfPageName = "/" + textOfPageName;
    page.textOfPages = readPageFile((argv1 + textOfPageName).c_str());
    for (std::vector<std::string>::iterator j = allChoices.begin(); j != allChoices.end();
         ++j) {
      size_t firstColon = (*j).find(':');
      size_t secondColon = (*j).find_last_of(':');
      size_t page_num;
      size_t dest_num;
      std::string choiceText;

      page_num = atoi(((*j).substr(firstColon - 1, 1)).c_str());
      dest_num =
          atoi(((*j).substr(firstColon + 1, secondColon - firstColon - 1)).c_str());
      choiceText = (*j).substr(secondColon + 1);

      if (page_num == page.pageNum) {
        page.choices.push_back(std::make_pair(dest_num, choiceText));
      }
    }
    pages.push_back(page);
  }
  return pages;
}
