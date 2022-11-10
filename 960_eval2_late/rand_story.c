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

  const char * ptr1 = line;
  const char * ptr2 = line;

  while (*ptr1 != '\0') {
    termRes.termarr =
        realloc(termRes.termarr, (termRes.termNum + 1) * sizeof(*termRes.termarr));

    ptr1 = strchr(ptr1, ' ');

    if (ptr1 != NULL) {
      termRes.termarr[termRes.termNum] =
          malloc((ptr1 - ptr2 + 1) * sizeof(*termRes.termarr[termRes.termNum]));

      strncpy(termRes.termarr[termRes.termNum], ptr2, ptr1 - ptr2);
      termRes.termarr[termRes.termNum][ptr1 - ptr2] = '\0';

      ptr1++;
      ptr2 = ptr1;

      termRes.termNum++;
    }

    else {
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

  outputTerms.termarr = malloc((inputTerms.termNum) * sizeof(*outputTerms.termarr));

  for (size_t i = 0; i < inputTerms.termNum; i++) {
    const char * ptr1 = inputTerms.termarr[i];
    const char * ptr2 = inputTerms.termarr[i];
    const char * end_ptr = &inputTerms.termarr[i][strlen(inputTerms.termarr[i]) - 1];

    outputTerms.termarr[i] =
        malloc((strlen(inputTerms.termarr[i]) + 1) * sizeof(*outputTerms.termarr[i]));

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

termInfo_t cd_underscore(termInfo_t inputTerms, catarray_t * cats) {
  termInfo_t outputTerms;
  outputTerms.termarr = NULL;
  outputTerms.termNum = inputTerms.termNum;

  outputTerms.termarr = malloc((inputTerms.termNum) * sizeof(*outputTerms.termarr));

  prevWords_t list;
  list.words = NULL;
  list.num = 0;

  for (size_t i = 0; i < inputTerms.termNum; i++) {
    const char * ptr1 = inputTerms.termarr[i];
    const char * ptr2 = inputTerms.termarr[i];
    const char * end_ptr = &inputTerms.termarr[i][strlen(inputTerms.termarr[i]) - 1];

    outputTerms.termarr[i] =
        malloc((strlen(inputTerms.termarr[i]) + 1) * sizeof(*outputTerms.termarr[i]));

    while (ptr1 != NULL) {
      ptr1 = strchr(ptr1, '_');
      ptr2 = strrchr(ptr2, '_');

      if (ptr1 != NULL) {
        strncpy(outputTerms.termarr[i], ptr1 + 1, ptr2 - ptr1 - 1);

        if (atoi(outputTerms.termarr[i]) == 0) {
          const char * stringcat = NULL;
          stringcat = chooseWord(outputTerms.termarr[i], cats);
          strcpy(outputTerms.termarr[i], stringcat);

          //store in prevWords list
          list.num++;
          list.words = realloc(list.words, list.num * sizeof(*list.words));
          list.words[list.num - 1] =
              malloc((strlen(stringcat) + 1) * sizeof(*list.words[list.num - 1]));
          strcpy(list.words[list.num - 1], stringcat);
        }

        else {
          //if it's number _1_ or _2_
          int index = atoi(outputTerms.termarr[i]);
          strcpy(outputTerms.termarr[i], list.words[list.num - index]);

          //store the words that used
          list.num++;
          list.words = realloc(list.words, list.num * sizeof(*list.words));
          list.words[list.num - 1] = malloc((strlen(outputTerms.termarr[i]) + 1) *
                                            sizeof(*list.words[list.num - 1]));
          strcpy(list.words[list.num - 1], outputTerms.termarr[i]);
        }
        if (*end_ptr != '_') {
          const char * ptr3 = ptr2 + 1;
          strcat(outputTerms.termarr[i], ptr3);
        }
        break;
      }

      else {
        strcpy(outputTerms.termarr[i], inputTerms.termarr[i]);
      }
    }
  }

  return outputTerms;
}

void printTermInfo(termInfo_t termRes) {
  for (size_t i = 0; i < termRes.termNum; i++) {
    if (i != termRes.termNum - 1) {
      printf("%s ", termRes.termarr[i]);
    }
    else {
      printf("%s", termRes.termarr[i]);
    }
  }
}

void freeTermInfo(termInfo_t termRes) {
  for (size_t i = 0; i < termRes.termNum; i++) {
    free(termRes.termarr[i]);
  }
  free(termRes.termarr);
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
    ptr1 = strchr(ptr1, ':');
    while (*ptr1 != '\0') {
      res.cat = malloc((ptr1 - ptr2 + 1) * sizeof(*res.cat));

      if (ptr1 != NULL) {
        strncpy(res.cat, ptr2, ptr1 - ptr2);
        res.cat[ptr1 - ptr2] = '\0';
        ptr1++;
        ptr2 = ptr1;

        counter++;
        break;
      }

      else {
        break;
      }
      break;
    }

    edptr = strchr(line, '\n');
    mdptr = strchr(line, ':');

    res.name = malloc((edptr - mdptr) * sizeof(*res.name));
    strncpy(res.name, mdptr + 1, edptr - mdptr - 1);
    res.name[edptr - mdptr - 1] = '\0';

    counter++;

    if (counter != 2) {
      fprintf(stderr, "Line have an incorrect number of elements\n");
      exit(EXIT_FAILURE);
    }
  }
  return res;
}

catarray_t arrDeepCopy(catarray_t inputArr) {
  catarray_t outputArr;
  outputArr.arr = NULL;
  outputArr.n = 0;

  outputArr.n = inputArr.n;

  outputArr.arr = malloc(outputArr.n * sizeof(*outputArr.arr));

  for (size_t i = 0; i < outputArr.n; i++) {
    outputArr.arr[i].n_words = inputArr.arr[i].n_words;
    outputArr.arr[i].name =
        malloc((strlen(inputArr.arr[i].name) + 1) * sizeof(*outputArr.arr[i].name));
    strcpy(outputArr.arr[i].name, inputArr.arr[i].name);

    outputArr.arr[i].words =
        malloc(outputArr.arr[i].n_words * sizeof(*outputArr.arr[i].words));

    for (size_t j = 0; j < outputArr.arr[i].n_words; j++) {
      outputArr.arr[i].words[j] = malloc((strlen(inputArr.arr[i].words[j]) + 1) *
                                         sizeof(*outputArr.arr[i].words[j]));
      strcpy(outputArr.arr[i].words[j], inputArr.arr[i].words[j]);
    }
  }

  return outputArr;
}

catarray_t storeNewArr(catInfo_t res, catarray_t savedres) {
  savedres.n++;

  savedres.arr = realloc(savedres.arr, savedres.n * sizeof(*savedres.arr));

  savedres.arr[savedres.n - 1].name = NULL;
  savedres.arr[savedres.n - 1].n_words = 0;

  savedres.arr[savedres.n - 1].name =
      malloc((strlen(res.cat) + 1) *
             sizeof(*savedres.arr[savedres.n - 1].name));  // may need to fix
  strcpy(savedres.arr[savedres.n - 1].name, res.cat);
  /*
  for (size_t i = 0; i < strlen(res.cat); i++) {
    savedres.arr[savedres.n - 1].name[i] = res.cat[i];
    }*/
  //savedres.arr[savedres.n - 1].name = res.cat;

  //  savedres.arr[savedres.n - 1].n_words = 0;
  savedres.arr[savedres.n - 1].n_words++;

  savedres.arr[savedres.n - 1].words = malloc(
      savedres.arr[savedres.n - 1].n_words * sizeof(*savedres.arr[savedres.n - 1].words));

  savedres.arr[savedres.n - 1].words[0] = NULL;
  savedres.arr[savedres.n - 1].words[0] =
      malloc((strlen(res.name) + 1) * sizeof(*savedres.arr[savedres.n - 1].words[0]));
  strcpy(savedres.arr[savedres.n - 1].words[0], res.name);

  /*
  for (size_t i = 0; i < strlen(res.name); i++) {
    savedres.arr[savedres.n - 1].words[0][i] = res.name[i];
    }*/
  //savedres.arr[savedres.n - 1].words[0] = res.name;

  return savedres;
}

catarray_t storeRes(catInfo_t res, catarray_t savedres) {
  size_t count = 0;
  for (size_t i = 0; i < savedres.n; i++) {
    if (strcmp(savedres.arr[i].name, res.cat) == 0) {
      savedres.arr[i].n_words++;

      savedres.arr[i].words =
          realloc(savedres.arr[i].words,
                  savedres.arr[i].n_words * sizeof(*savedres.arr[i].words));

      savedres.arr[i].words[savedres.arr[i].n_words - 1] =
          malloc((strlen(res.name) + 1) *
                 sizeof(*savedres.arr[i].words[savedres.arr[i].n_words - 1]));

      strcpy(savedres.arr[i].words[savedres.arr[i].n_words - 1], res.name);
      /*
      for (size_t j = 0; i < strlen(res.name); i++) {
        savedres.arr[i].words[savedres.arr[i].n_words - 1][j] = res.name[j];
	}*/
      //savedres.arr[i].words[savedres.arr[i].n_words - 1] = res.name;
      count++;
    }
    count++;
  }

  if (count == savedres.n) {
    savedres = storeNewArr(res, savedres);
  }

  return savedres;
}

void freeSavedRes(catarray_t savedres) {
  for (size_t i = 0; i < savedres.n; i++) {
    free(savedres.arr[i].name);
    for (size_t j = 0; j < savedres.arr[i].n_words; j++) {
      free(savedres.arr[i].words[j]);
    }
    free(savedres.arr[i].words);
  }
  free(savedres.arr);
}
