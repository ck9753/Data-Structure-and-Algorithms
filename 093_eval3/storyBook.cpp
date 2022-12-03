#include "storyBook.hpp"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

// from readStory class, store pages vector to pages in storyBook class
void storyBook::runStoryBook(const char * dir) {
  readStory file;
  file.readStoryFile(dir);

  pages = file.storeParsedDataToPage(dir);

  checkValidity();
}

// check three conditions for validity
void storyBook::checkValidity() {
  std::vector<size_t> possiblePages;
  std::vector<size_t> possibleChoicesDest;

  // checker to check if pages have at least a WIN and a LOSE page
  size_t checkWin = 0;
  size_t checkLose = 0;

  for (std::vector<std::pair<size_t, Page> >::iterator i = pages.begin();
       i != pages.end();
       ++i) {
    possiblePages.push_back((*i).first);
    for (std::vector<std::pair<size_t, std::string> >::iterator j =
             (*i).second.choices.begin();
         j != (*i).second.choices.end();
         ++j) {
      possibleChoicesDest.push_back((*j).first);
    }

    // 3c. At least one page must be a WIN page and at least one page must be a LOSE page
    if ((*i).second.pageType == "W") {
      checkWin = 1;
    }

    else if ((*i).second.pageType == "L") {
      checkLose = 1;
    }
  }

  if (checkWin == 0 || checkLose == 0) {
    std::cerr << "At least one page must be a WIN page and at least one page must be a "
                 "LOSE page."
              << std::endl;
    exit(EXIT_FAILURE);
  }

  // 3a. Every page that is referenced by a choice is valid
  size_t checkChoices = 0;  // checker to check if destNum exist in pages
  for (std::vector<size_t>::iterator destIter = possibleChoicesDest.begin();
       destIter != possibleChoicesDest.end();
       ++destIter) {
    for (std::vector<size_t>::iterator pageIter = possiblePages.begin();
         pageIter != possiblePages.end();
         ++pageIter) {
      if (*destIter == *pageIter) {
        checkChoices = 1;
      }
    }
  }
  if (checkChoices != 1) {
    std::cerr << "Every page that is referenced by a choice should be valid" << std::endl;
    exit(EXIT_FAILURE);
  }

  // 3b. Every page (except page 0) is referenced by at least one *other* page's choices.
  size_t checkPages = 0;
  for (std::vector<size_t>::iterator pageIter = possiblePages.begin();
       pageIter != possiblePages.end();
       ++pageIter) {
    if (*pageIter != 0) {
      for (std::vector<size_t>::iterator destIter = possibleChoicesDest.begin();
           destIter != possibleChoicesDest.end();
           ++destIter) {
        if (*pageIter == *destIter) {
          checkPages = 1;
        }
      }
    }
  }
  if (checkPages != 1) {
    std::cerr << "Every page (except page 0) should be referenced by at least one "
                 "other page's choices."
              << std::endl;
    exit(EXIT_FAILURE);
  }
}

bool storyBook::checkUserChoice(size_t userChoice, size_t presentPageNum) {
  // check if user input is smaller than 1 (userChoice = 0 if input is not string)
  if (userChoice < 1) {
    return false;
  }

  // check if user input is greater than the number of choices
  if (userChoice > pages[presentPageNum].second.choices.size()) {
    return false;
  }
  return true;
}

void storyBook::processPages() {
  // print the Page 0
  pages[0].second.printPage();

  // index for present page number
  size_t presentPageNum = 0;
  // index for checking gameOver
  bool gameOver = false;

  while (!gameOver) {
    // declare input from user
    std::string input;

    // read input
    std::getline(std::cin, input);

    size_t userChoice = atoi(input.c_str());

    if (checkUserChoice(userChoice, presentPageNum) == false) {
      std::cout << "That is not a valid choice, please try again" << std::endl;
    }

    else {
      std::pair<size_t, std::string> userChoicePair =
          pages[presentPageNum].second.choices[userChoice - 1];

      presentPageNum = userChoicePair.first;

      pages[presentPageNum].second.printPage();

      // if pageType is W or L, the game is over and the while loop is stopped
      if (pages[presentPageNum].second.pageType == "W" ||
          pages[presentPageNum].second.pageType == "L") {
        gameOver = true;
      }
    }
  }
}

std::vector<Page> storyBook::dfs(Page start, Page end) {
  std::stack<std::vector<Page> > pathStack;
  std::vector<Page> visited;
  std::vector<Page> invalid;

  // create vector of start Page for stack
  std::vector<Page> startVector;
  startVector.push_back(start);

  pathStack.push(startVector);

  while (pathStack.empty() != 1) {
    std::vector<Page> currentPath = pathStack.top();
    pathStack.pop();

    Page currentNode = currentPath.back();

    if (currentNode.pageNum == end.pageNum) {
      return currentPath;
    }

    // check if currentNode is in visited
    size_t visitedFlag = 0;
    for (std::vector<Page>::iterator it = visited.begin(); it != visited.end(); it++) {
      if ((*it).pageNum == currentNode.pageNum) {
        visitedFlag = 1;
      }
    }

    if (visitedFlag != 1) {
      visited.push_back(currentNode);

      for (std::vector<std::pair<size_t, std::string> >::iterator it =
               currentNode.choices.begin();
           it != currentNode.choices.end();
           it++) {
        currentPath.push_back(
            pages[(*it).first]
                .second);  // should check if it's (*it).first - 1 instead or not
        pathStack.push(currentPath);
        currentPath.pop_back();
      }
    }
  }
  return invalid;
}

void storyBook::printCurrentPath(std::vector<Page> currentPath) {
  if (currentPath.empty()) {
    std::cout << "This story is unwinnable!" << std::endl;
  }

  // if the story is winnable
  else {
    size_t currentPathLen = currentPath.size();
    size_t currentPathCtr = 0;
    for (std::vector<Page>::iterator i = currentPath.begin(); i != currentPath.end();
         i++) {
      currentPathCtr++;
      size_t curr_pageNum = (*i).pageNum;
      size_t next_pageNum;
      if (currentPathCtr < currentPathLen) {
        next_pageNum = (*(i + 1)).pageNum;
      }

      size_t userChoiceNum;
      size_t choicesCtr = 0;  // counter for choices vector to find index
      for (std::vector<std::pair<size_t, std::string> >::iterator j =
               (*i).choices.begin();
           j != (*i).choices.end();
           j++) {
        if ((*j).first == next_pageNum) {
          userChoiceNum = choicesCtr;
        }
        choicesCtr++;
      }

      if (currentPathCtr < currentPathLen) {
        std::cout << curr_pageNum << "(" << userChoiceNum << "),";
      }
      else {
        std::cout << curr_pageNum << "(win)";
      }
    }
  }
}
void storyBook::findWaysToWin() {
  for (std::vector<std::pair<size_t, Page> >::iterator it = pages.begin();
       it != pages.end();
       it++) {
    if ((*it).second.pageType == "W") {
      std::vector<Page> currentPath;
      currentPath =
          dfs(pages[0].second,
              (*it).second);  // dfs with page0 for start and page with win for end
      // print currentPath
      printCurrentPath(currentPath);
      std::cout << "\n";
    }
  }
}
