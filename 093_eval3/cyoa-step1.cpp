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
  std::vector<std::pair<size_t, Page> > pages;

  if (file.readStoryFile(argv[1]) == false) {
    std::cerr << "unavailable to open story.txt file" << std::endl;
    exit(EXIT_FAILURE);
  }

  pages = file.storeParsedDataToPage(argv[1]);

  for (std::vector<std::pair<size_t, Page> >::iterator i = pages.begin();
       i != pages.end();
       ++i) {
    Page page;
    page = (*i).second;

    std::cout << "Page " << (*i).first << std::endl;
    std::cout << "==========" << std::endl;

    page.printPage();
  }
}
