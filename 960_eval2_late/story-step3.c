#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  // check if the user types correct commands
  if (argc != 3) {
    fprintf(stderr, "Incorrect Commands\n");
    exit(EXIT_FAILURE);
  }

  FILE * cat_words = fopen(argv[1], "r");
  FILE * st_tmpl = fopen(argv[2], "r");

  checkFileOpen(cat_words, st_tmpl);

  // initialize pointers of lines and sizes
  char * line1 = NULL;
  char * line2 = NULL;
  size_t sz1 = 0;
  size_t sz2 = 0;

  // declare and initialize catarray_t struct
  catarray_t savedcat;
  savedcat.arr = NULL;
  savedcat.n = 0;

  // declare line number counter
  size_t lenNum = 0;

  while (getline(&line1, &sz1, cat_words) >= 0) {
    lenNum++;

    // declare and initialize catInfo_t res
    catInfo_t res;
    res.cat = NULL;
    res.name = NULL;

    // get result parsed by the delimiter ':'
    res = parseLineSemi(line1);

    // if the line1 is the first line, use the function storeNewArr
    if (lenNum == 1) {
      savedcat = storeNewArr(res, savedcat);

      // free res
      free(res.cat);
      free(res.name);
    }

    // otherwise, use the function storeRes
    else {
      savedcat = storeRes(res, savedcat);

      // free res
      free(res.cat);
      free(res.name);
    }
  }
  // free line1 once every line has been read
  free(line1);

  // store savedcat result to inputCat
  catarray_t * inputCat = &savedcat;

  // declare and initialize prevWordsList
  prevWords_t prevWordsList;
  prevWordsList.words = NULL;
  prevWordsList.num = 0;

  while (getline(&line2, &sz2, st_tmpl) >= 0) {
    // declare and initialize termInfo_t termRes struct
    termInfo_t termRes;
    termRes.termarr = NULL;
    termRes.termNum = 0;

    // store result of parseTerm in termRes
    termRes = parseTerm(line2);

    // declare and initialize termInfo_t termRes2 struct
    termInfo_t termRes2;
    termRes2.termarr = NULL;
    termRes2.termNum = 0;

    // store result of cd_underscore in termRes2
    termRes2 = cd_underscore(termRes, inputCat, prevWordsList, 0);

    //copy and store list to prevwordsList
    prevWordsList = cpList(termRes2.list);

    //free termRes struct
    freeTermInfo(termRes);

    //print termRes2
    printTermInfo(termRes2);

    // free termRes struct
    freeTermInfo(termRes2);
    // free list struct inside termRes strcut
    freeListinTermInfo(termRes2);
  }
  // free List, line2, and savedcat
  freeList(prevWordsList);
  free(line2);
  freeSavedRes(savedcat);

  // check if the file for story template is closed
  if (fclose(st_tmpl) != 0) {
    fprintf(stderr, "Story template file fail to close\n");
    exit(EXIT_FAILURE);
  }

  // check if the file with categories/words is closed
  if (fclose(cat_words) != 0) {
    fprintf(stderr, "A file with the categories/words fail to close\n");
    exit(EXIT_FAILURE);
  }
}
