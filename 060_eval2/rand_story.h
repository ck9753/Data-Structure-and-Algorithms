#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>

#include "provided.h"

//any functions you want your main to use
struct _termInfo_t {
  char ** termarr;
  size_t termNum;
};
typedef struct _termInfo_t termInfo_t;

struct _catInfo_t {
  char * cat;
  char * name;
};
typedef struct _catInfo_t catInfo_t;

termInfo_t parseTerm(char * line);

termInfo_t rmUnderScore(termInfo_t inputTerms);

catInfo_t parseLineSemi(char * line);

catarray_t storeNewArr(catInfo_t res, catarray_t savedres);

catarray_t storeRes(catInfo_t res, catarray_t savedres);
#endif
