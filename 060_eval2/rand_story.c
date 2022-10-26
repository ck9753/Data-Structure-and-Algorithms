#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

termInfo_t parseTerm(char * line) {
  termInfo_t termRes;
  termRes.termarr = NULL;
  termRes.termNum = 0;
  //char ** termarr = NULL;
  //size_t num = 0;

  termRes.termarr = malloc((termRes.termNum + 1) * sizeof(*termRes.termarr));

  const char * ptr1 = line;
  const char * ptr2 = line;
  //size_t i = 0;  //counter for termarr
  while (*ptr1 != '\0') {
    termRes.termarr =
        realloc(termRes.termarr, (termRes.termNum + 1) * sizeof(*termRes.termarr));
    ptr1 = strchr(ptr1, ' ');

    if (ptr1 != NULL) {
      termRes.termarr[termRes.termNum] =
          malloc((ptr1 - ptr2) * sizeof(*termRes.termarr[termRes.termNum]));
      strncpy(termRes.termarr[termRes.termNum], ptr2, ptr1 - ptr2);
      ptr1++;
      ptr2 = ptr1;

      termRes.termNum++;
    }

    else {
      ptr1 = ptr2;
      ptr2 = strchr(ptr2, '\0');
      termRes.termarr[termRes.termNum] =
          malloc((ptr2 - ptr1) * sizeof(*termRes.termarr[termRes.termNum]));
      strcpy(termRes.termarr[termRes.termNum], ptr1);

      termRes.termNum++;
      break;
    }
  }

  return termRes;
}

termInfo_t rmUnderScore(termInfo_t inputTerms) {
  termInfo_t outputTerms;
  outputTerms.termarr = NULL;
  outputTerms.termNum = inputTerms.termNum;

  outputTerms.termarr = malloc(sizeof(*inputTerms.termarr));

  for (size_t i = 0; i < inputTerms.termNum; i++) {
    const char * ptr1 = inputTerms.termarr[i];
    const char * ptr2 = inputTerms.termarr[i];
    const char * end_ptr = &inputTerms.termarr[i][sizeof(inputTerms.termarr[i]) - 1];

    outputTerms.termarr[i] = malloc(sizeof(*inputTerms.termarr[i]));  //should fix?
    //outputTerms.termNum = inputTerms.termNum;
    /*
      while (ptr1 != NULL) {*/
    ptr1 = strchr(ptr1, '_');
    ptr2 = strrchr(ptr2, '_');

    if (ptr1 != NULL) {
      strncpy(outputTerms.termarr[i], ptr1 + 1, ptr2 - ptr1 - 1);
      const char * stringcat = chooseWord(outputTerms.termarr[i], NULL);
      strcpy(outputTerms.termarr[i], stringcat);
      if (*end_ptr != '_') {
        //char * append = NULL;
        const char * ptr3 = ptr2 + 1;
        //strcpy(append, ptr3);
        strcat(outputTerms.termarr[i], ptr3);
        break;
      }
      break;
    }

    else {
      strcpy(outputTerms.termarr[i], inputTerms.termarr[i]);
      break;
    }
  }
  return outputTerms;
}
