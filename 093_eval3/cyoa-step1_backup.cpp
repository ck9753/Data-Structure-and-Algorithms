#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "page.hpp"

int main(int argc, char * argv[]) {
  if (argc != 2) {
    std::cerr << "Wrong command format. Expected: ./cyoa-step1 story_irectory address\n"
              << std::endl;
    exit(EXIT_FAILURE);
  }

  readStory file;
  //std::string storyTxt = "/story.txt";
  //storyTxt = argv[1] + storyTxt;

  file.readStoryFile(argv[1]);
  /*
  if (file.readStoryFile(storyTxt.c_str()) == false) {
    std::cerr << "unavailable to open story.txt file" << std::endl;
    exit(EXIT_FAILURE);
  }
  */

  size_t pageNum_declar;
  size_t pageNum_choice;
  std::string pageType;
  std::string textOfThePageName;
  std::vector<std::string> pageText;
  std::string choiceOfThePage;

  // can use file.allPagedeclaration, file.allChoices
  for (std::vector<std::string>::iterator i = file.allPageDeclaration.begin();
       i != file.allPageDeclaration.end();
       ++i) {
    // find pageNum and pageType
    int atIndex = (*i).find('@');
    int colonIndex = (*i).find(':');

    if (atIndex == 1) {
      pageNum_declar = atoi(((*i).substr(atIndex - 1, 1)).c_str());
    }

    else if (atIndex == 2) {
      pageNum_declar = atoi(((*i).substr(atIndex - 2, 2)).c_str());
    }

    pageType = (*i).substr(atIndex + 1, 1);
    textOfThePageName = (*i).substr(++colonIndex);
    textOfThePageName = "/" + textOfThePageName;

    std::cout << "Page " << pageNum_declar << std::endl;
    std::cout << "==========" << std::endl;
    pageText = file.readPageFile((argv[1] + textOfThePageName).c_str());
    file.printPage(pageText);

    if (pageType == "W") {
      std::cout << "Congratulations! You have won. Hooray!" << std::endl;
      // should check
    }

    else if (pageType == "L") {
      std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
      //break;  // should check
    }

    else {
      std::cout << "What would you like to do?"
                << "\n"
                << std::endl;

      // counter for choice index
      int k = 1;
      for (std::vector<std::string>::iterator j = file.allChoices.begin();
           j != file.allChoices.end();
           ++j) {
        int firstColonIndex = (*j).find(':');
        int secondColonIndex = (*j).find_last_of(':');

        pageNum_choice = atoi(((*j).substr(firstColonIndex - 1, 1)).c_str());
        choiceOfThePage = (*j).substr(secondColonIndex + 1);

        if (pageNum_choice == pageNum_declar) {
          std::cout << k << ". " << choiceOfThePage << std::endl;
          k++;
        }
      }
    }
  }
}
