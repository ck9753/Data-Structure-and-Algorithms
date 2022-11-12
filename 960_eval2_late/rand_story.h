#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>

#include "provided.h"

//any functions you want your main to use
struct _prevWords_t {
  char ** words;
  size_t num;
};
typedef struct _prevWords_t prevWords_t;

struct _termInfo_t {
  char ** termarr;
  size_t termNum;
  size_t * space;
  prevWords_t list;
};
typedef struct _termInfo_t termInfo_t;

struct _catInfo_t {
  char * cat;
  char * name;
};
typedef struct _catInfo_t catInfo_t;

termInfo_t parseTerm(char * line);

termInfo_t cdCatToWord(termInfo_t inputTerms, catarray_t * cats);

termInfo_t cd_underscore(termInfo_t inputTerms,
                         catarray_t * cats,
                         prevWords_t list,
                         int ind);

void freeTermInfo(termInfo_t termRes);

void freeList(prevWords_t list);

void freeListinTermInfo(termInfo_t termRes);

prevWords_t cpList(prevWords_t inputlist);

void printTermInfo(termInfo_t termRes);

catInfo_t parseLineSemi(char * line);

catarray_t arrDeepCopy(catarray_t inputArr);

catarray_t storeNewArr(catInfo_t res, catarray_t savedres);

catarray_t storeRes(catInfo_t res, catarray_t savedres);

void freeSavedRes(catarray_t savedres);

void checkFileOpen(FILE * catF, FILE * tmpF);

void checkFileClosed(FILE * catF, FILE * tmpF);

catarray_t savedCatfor4(FILE * catF, catarray_t savedcat);

void cd_underscorefor4(FILE * tmpF, catarray_t savedcat, catarray_t * inputCat, int n);
#endif
