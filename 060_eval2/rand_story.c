#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

termInfo_t parseTerm(char * line) {
  termInfo_t termRes;
  termRes.termarr = NULL;
  termRes.termNum = 0;

  termRes.termarr = malloc(sizeof(*termRes.termarr));
  //termRes.eachTermNum = malloc(sizeof(*termRes.eachTermNum));

  //termRes.termarr[termRes.termNum] = NULL;

  const char * ptr1 = line;
  const char * ptr2 = line;
  //size_t i = 0;  //counter for termarr
  while (*ptr1 != '\0') {
    //termRes.termarr[termRes.termNum + 1] = NULL;
    termRes.termarr =
        realloc(termRes.termarr, (termRes.termNum + 1) * sizeof(*termRes.termarr));
    /*termRes.eachTermNum = realloc(termRes.eachTermNum,
                                  (termRes.termNum + 1) * sizeof(*termRes.eachTermNum));
    termRes.eachTermNum[termRes.termNum] = 0;
    */
    ptr1 = strchr(ptr1, ' ');

    if (ptr1 != NULL) {
      termRes.termarr[termRes.termNum] =
          malloc((ptr1 - ptr2 + 1) * sizeof(*termRes.termarr[termRes.termNum]));
      //termRes.eachTermNum[termRes.termNum] = ptr1 - ptr2 + 1;
      strncpy(termRes.termarr[termRes.termNum], ptr2, ptr1 - ptr2);
      termRes.termarr[termRes.termNum][ptr1 - ptr2] = '\0';

      ptr1++;
      ptr2 = ptr1;

      termRes.termNum++;
    }

    else {
      //termRes.eachTermNum[termRes.termNum] = ptr1 - ptr2;
      ptr1 = ptr2;
      ptr2 = strchr(ptr2, '\0');
      termRes.termarr[termRes.termNum] =
          malloc((ptr2 - ptr1 + 1) * sizeof(*termRes.termarr[termRes.termNum]));

      strncpy(termRes.termarr[termRes.termNum], ptr1, ptr2 - ptr1 + 1);

      termRes.termNum++;
      break;
    }
  }

  return termRes;
}

termInfo_t rmUnderScore(termInfo_t inputTerms, catarray_t * cats) {
  termInfo_t outputTerms;
  outputTerms.termarr = NULL;
  outputTerms.termNum = inputTerms.termNum;
  //outputTerms.eachTermNum = NULL;

  outputTerms.termarr = malloc((inputTerms.termNum) * sizeof(*outputTerms.termarr));
  /*outputTerms.eachTermNum =
      malloc((inputTerms.termNum) * sizeof(*outputTerms.eachTermNum));
      
  outputTerms.eachTermNum = inputTerms.eachTermNum;
  */
  for (size_t i = 0; i < inputTerms.termNum; i++) {
    const char * ptr1 = inputTerms.termarr[i];
    const char * ptr2 = inputTerms.termarr[i];
    const char * end_ptr = &inputTerms.termarr[i][strlen(inputTerms.termarr[i]) - 1];

    //outputTerms.termarr[i] = NULL;
    outputTerms.termarr[i] =
        malloc((strlen(inputTerms.termarr[i]) + 1) * sizeof(*outputTerms.termarr[i]));
    //malloc(inputTerms.eachTermNum[i] *sizeof(*outputTerms.termarr[i]));  //makes segfault
    //strlen(inputTerms.termarr[i]) + 1) * sizeof(*outputTerms.termarr[i]));

    while (ptr1 != NULL) {
      ptr1 = strchr(ptr1, '_');
      ptr2 = strrchr(ptr2, '_');

      if (ptr1 != NULL) {
        strncpy(outputTerms.termarr[i], ptr1 + 1, ptr2 - ptr1 - 1);
        const char * stringcat = NULL;
        stringcat = chooseWord(outputTerms.termarr[i], cats);
        strcpy(outputTerms.termarr[i], stringcat);
        if (*end_ptr != '_') {
          const char * ptr3 = ptr2 + 1;
          strcat(outputTerms.termarr[i], ptr3);
          //break;
        }
        break;
      }

      else {
        strcpy(outputTerms.termarr[i], inputTerms.termarr[i]);
        //break;
      }
    }
  }
  return outputTerms;
}

catInfo_t parseLineSemi(char * line) {
  catInfo_t res;
  res.cat = NULL;
  res.name = NULL;

  size_t counter = 0;

  const char * ptr1 = line;
  const char * ptr2 = line;
  const char * edptr = line;
  const char * mdptr = line;

  // check if the line is empty
  if ((line == NULL) || (strlen(line) == 0)) {
    fprintf(stderr, "Line is empty\n");
    exit(EXIT_FAILURE);
  }
  // check if the line does not include :
  else if (strchr(line, ':') == NULL) {
    fprintf(stderr, "Line does not include semicolon(:)\n");
    exit(EXIT_FAILURE);
  }

  else {
    while (*ptr1 != '\0') {
      ptr1 = strchr(ptr1, ':');

      res.cat = malloc((ptr1 - ptr2 + 1) * sizeof(*res.cat));

      if (ptr1 != NULL) {
        strncpy(res.cat, ptr2, ptr1 - ptr2);
        ptr1++;
        ptr2 = ptr1;

        counter++;
        break;
      }

      else {
        break;
      }
    }

    edptr = strchr(line, '\n');
    mdptr = strchr(line, ':');

    res.name = malloc((edptr - mdptr) * sizeof(*res.name));
    strncpy(res.name, mdptr + 1, edptr - mdptr - 1);
    counter++;

    if (counter != 2) {
      fprintf(stderr, "Line have an incorrect number of elements\n");
      exit(EXIT_FAILURE);
    }
  }
  return res;
}

catarray_t storeNewArr(catInfo_t res, catarray_t savedres) {
  savedres.n++;

  savedres.arr = realloc(savedres.arr, savedres.n * sizeof(*savedres.arr));
  //  savedres.arr
  savedres.arr[savedres.n - 1].name = malloc(
      strlen(res.cat) * sizeof(*savedres.arr[savedres.n - 1].name));  // may need to fix
  savedres.arr[savedres.n - 1].name = res.cat;

  savedres.arr[savedres.n - 1].n_words++;

  savedres.arr[savedres.n - 1].words = malloc(
      savedres.arr[savedres.n - 1].n_words * sizeof(*savedres.arr[savedres.n - 1].words));

  savedres.arr[savedres.n - 1].words[0] =
      malloc(strlen(res.name) * sizeof(*savedres.arr[savedres.n - 1].words[0]));

  savedres.arr[savedres.n - 1].words[0] = res.name;

  return savedres;
}

catarray_t storeRes(catInfo_t res, catarray_t savedres) {
  size_t count = 0;
  for (size_t i = 0; i < savedres.n; i++) {
    if (strcmp(savedres.arr[i].name, res.cat) == 0) {
      savedres.arr[savedres.n - 1].n_words++;
      savedres.arr[savedres.n - 1].words[savedres.arr[savedres.n - 1].n_words - 1] =
          malloc(strlen(res.name) *
                 sizeof(*savedres.arr[savedres.n - 1]
                             .words[savedres.arr[savedres.n - 1].n_words - 1]));
      savedres.arr[savedres.n - 1].words[savedres.arr[savedres.n - 1].n_words - 1] =
          res.name;
      count++;
    }
    count++;
  }

  if (count == savedres.n) {
    savedres = storeNewArr(res, savedres);
  }

  return savedres;
}
