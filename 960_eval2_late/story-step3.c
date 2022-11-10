#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Incorrect Commands\n");
    exit(EXIT_FAILURE);
  }

  FILE * cat_words = fopen(argv[1], "r");
  FILE * st_tmpl = fopen(argv[2], "r");

  if (cat_words == NULL) {
    fprintf(stderr, "Could not open a file with the categories/words\n");
    exit(EXIT_FAILURE);
  }

  if (st_tmpl == NULL) {
    fprintf(stderr, "Could not open a story template file\n");
    exit(EXIT_FAILURE);
  }

  char * line1 = NULL;
  char * line2 = NULL;
  size_t sz1 = 0;
  size_t sz2 = 0;

  catarray_t savedcat;
  savedcat.arr = NULL;
  savedcat.n = 0;
  size_t lenNum = 0;
  //char ** temparr = NULL;
  //size_t tempNum = 0;

  while (getline(&line1, &sz1, cat_words) >= 0) {
    lenNum++;
    catInfo_t res;

    res.cat = NULL;
    res.name = NULL;

    res = parseLineSemi(line1);

    if (lenNum == 1) {
      savedcat = storeNewArr(res, savedcat);
    }
    else {
      savedcat = storeRes(res, savedcat);
    }
  }
  free(line1);
  catarray_t * inputCat = &savedcat;

  while (getline(&line2, &sz2, st_tmpl) >= 0) {
    termInfo_t termRes;
    termRes.termarr = NULL;
    termRes.termNum = 0;
    termRes = parseTerm(line2);

    termInfo_t termRes2;
    termRes2.termarr = NULL;
    termRes2.termNum = 0;
    termRes2 = cd_underscore(termRes, inputCat);

    freeTermInfo(termRes);
    printTermInfo(termRes2);

    freeTermInfo(termRes2);

    //free(termRes.termarr);
    //temparr = termRes.termarr;
    //tempNum = termRes.termNum;
  }
  free(line2);

  if (fclose(st_tmpl) != 0) {
    fprintf(stderr, "Story template file fail to close\n");
    exit(EXIT_FAILURE);
  }

  if (fclose(cat_words) != 0) {
    fprintf(stderr, "A file with the categories/words fail to close\n");
    exit(EXIT_FAILURE);
  }
}
