#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

// function to parse term with the delimiter ' ' and '_'
termInfo_t parseTerm(char * line) {
  termInfo_t termRes;
  termRes.termarr = NULL;
  termRes.termNum = 0;
  termRes.space = NULL;

  // allocate memory for termarr and space
  termRes.termarr = malloc(sizeof(*termRes.termarr));
  termRes.space = malloc(sizeof(*termRes.termarr));

  const char * ptr1 = line;
  const char * ptr2 = line;
  const char * ptr3 = line;  // pointer for checkting if it's '_'

  while (*ptr1 != '\0') {
    // increase memory to add term
    termRes.termarr =
        realloc(termRes.termarr, (termRes.termNum + 1) * sizeof(*termRes.termarr));
    termRes.space =
        realloc(termRes.space, (termRes.termNum + 1) * sizeof(*termRes.space));

    // pointer for checking if '_' starts term
    if (ptr3 != NULL) {
      ptr3 = strchr(ptr3, '_');
    }

    ptr1 = strchr(ptr1, ' ');

    if (ptr1 != NULL) {
      // pointer for checking '_' not starting with space
      const char * ptr4 = ptr1;
      ptr4 = strchr(ptr4, '_');

      // if there's no space and '_'s are placed in strings
      if ((ptr2 != ptr3) && (ptr4 != ptr3)) {
        // store the first term
        termRes.termarr[termRes.termNum] =
            malloc((ptr3 - ptr2 + 1) * sizeof(termRes.termarr[termRes.termNum]));
        strncpy(termRes.termarr[termRes.termNum], ptr2, ptr3 - ptr2);
        termRes.termarr[termRes.termNum][ptr3 - ptr2] = '\0';

        // assign space index to 0
        termRes.space[termRes.termNum] = 0;

        termRes.termNum++;

        // store term with '_'s
        ptr1--;
        termRes.termarr =
            realloc(termRes.termarr, (termRes.termNum + 1) * sizeof(*termRes.termarr));

        termRes.termarr[termRes.termNum] =
            malloc((ptr4 - ptr1 + 2) * sizeof(*termRes.termarr[termRes.termNum]));

        strncpy(termRes.termarr[termRes.termNum], ptr1, ptr4 - ptr1 + 1);
        termRes.termarr[termRes.termNum][ptr4 - ptr1 + 1] = '\0';

        termRes.space =
            realloc(termRes.space, (termRes.termNum + 1) * sizeof(*termRes.space));

        // assign space index to 0
        termRes.space[termRes.termNum] = 0;

        ptr1 = ptr4 + 1;
        ptr2 = ptr1;
        ptr3 = ptr1;

        termRes.termNum++;
      }

      // if the term does not start with '_'
      else if ((ptr2 != ptr3) || (ptr3 == NULL)) {
        termRes.termarr[termRes.termNum] =
            malloc((ptr1 - ptr2 + 1) * sizeof(*termRes.termarr[termRes.termNum]));

        strncpy(termRes.termarr[termRes.termNum], ptr2, ptr1 - ptr2);
        termRes.termarr[termRes.termNum][ptr1 - ptr2] = '\0';

        // assign space index to 1
        termRes.space[termRes.termNum] = 1;

        ptr1++;
        ptr2 = ptr1;

        termRes.termNum++;
      }

      // if the term starts with '_'
      else if (ptr2 == ptr3) {
        ptr1 = ptr3 + 1;
        ptr1 = strchr(ptr1, '_');
        termRes.termarr[termRes.termNum] =
            malloc((ptr1 - ptr2 + 2) * sizeof(*termRes.termarr[termRes.termNum]));

        strncpy(termRes.termarr[termRes.termNum], ptr2, ptr1 - ptr2 + 1);
        termRes.termarr[termRes.termNum][ptr1 - ptr2 + 1] = '\0';

        // assign space index to 1
        termRes.space[termRes.termNum] = 1;

        // in case more strings exist after the second '_'
        if (*(ptr1 + 1) != ' ') {
          ptr1++;
          ptr2 = strchr(ptr1, ' ');

          // declare temporary memory for the rest
          char * rest = NULL;

          rest = malloc((ptr2 - ptr1 + 1) * sizeof(*rest));
          strncpy(rest, ptr1, ptr2 - ptr1);
          rest[ptr2 - ptr1] = '\0';

          termRes.termarr[termRes.termNum] =
              realloc(termRes.termarr[termRes.termNum],
                      (strlen(termRes.termarr[termRes.termNum]) + ptr2 - ptr1 + 1) *
                          sizeof(*termRes.termarr[termRes.termNum]));

          // store the rest of strings to termRes.termarr[termRes.termNum]
          strcat(termRes.termarr[termRes.termNum], rest);
          termRes.termarr[termRes.termNum][ptr2 - ptr3] = '\0';
          free(rest);
        }

        //termRes.termarr[termRes.termNum][ptr1 - ptr2 + 1] = '\0';

        ptr1 = strchr(ptr1, ' ');
        ptr1++;
        ptr2 = ptr1;
        ptr3 = ptr1;

        termRes.termNum++;
      }
    }

    // in case this term is the last term
    else {
      ptr1 = ptr2;
      ptr2 = strchr(ptr2, '\0');
      termRes.termarr[termRes.termNum] =
          malloc((ptr2 - ptr1 + 1) * sizeof(*termRes.termarr[termRes.termNum]));

      strncpy(termRes.termarr[termRes.termNum], ptr1, ptr2 - ptr1 + 1);

      termRes.space[termRes.termNum] = 1;

      termRes.termNum++;
      break;
    }
  }

  return termRes;
}

// the function to convert category to "cat"
termInfo_t cdCatToWord(termInfo_t inputTerms, catarray_t * cats) {
  termInfo_t outputTerms;
  outputTerms.termarr = NULL;
  outputTerms.termNum = inputTerms.termNum;
  outputTerms.space = NULL;

  // allocate memory for termarr and space
  outputTerms.termarr = malloc((inputTerms.termNum) * sizeof(*outputTerms.termarr));
  outputTerms.space = malloc((inputTerms.termNum) * sizeof(*outputTerms.space));

  for (size_t i = 0; i < inputTerms.termNum; i++) {
    const char * ptr1 = inputTerms.termarr[i];
    const char * ptr2 = inputTerms.termarr[i];
    const char * end_ptr = &inputTerms.termarr[i][strlen(inputTerms.termarr[i]) - 1];

    // store each space index to outputTerms
    outputTerms.space[i] = inputTerms.space[i];

    outputTerms.termarr[i] =
        malloc((strlen(inputTerms.termarr[i]) + 1) * sizeof(*outputTerms.termarr[i]));

    while (ptr1 != NULL) {
      ptr1 = strchr(ptr1, '_');
      ptr2 = strrchr(ptr2, '_');

      // if has '_'
      if (ptr1 != NULL) {
        // if '_'s are not a pair
        if (ptr1 == ptr2) {
          strcpy(outputTerms.termarr[i], inputTerms.termarr[i]);
          break;
        }

        // store the strings inside '_'s
        strncpy(outputTerms.termarr[i], ptr1 + 1, ptr2 - ptr1 - 1);

        // change termarr to stringcat output
        const char * stringcat = NULL;
        stringcat = chooseWord(outputTerms.termarr[i], cats);
        strcpy(outputTerms.termarr[i], stringcat);

        // if there are more strings after the last '_'
        if (*end_ptr != '_') {
          const char * ptr3 = ptr2 + 1;
          strcat(outputTerms.termarr[i], ptr3);
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

termInfo_t cd_underscore(termInfo_t inputTerms,
                         catarray_t * cats,
                         prevWords_t list,
                         int ind) {
  // declare and initialize outputTerms struct
  termInfo_t outputTerms;
  outputTerms.termarr = NULL;
  outputTerms.termNum = inputTerms.termNum;
  outputTerms.space = NULL;

  // allocate memory with the size of the number of term in inputTerms struct
  outputTerms.termarr = malloc((inputTerms.termNum) * sizeof(*outputTerms.termarr));
  outputTerms.space = malloc((inputTerms.termNum) * sizeof(*outputTerms.space));

  // initialize list with the argument list
  outputTerms.list.num = list.num;
  outputTerms.list.words = list.words;

  // getting each inputTerms.termarr[i] and process it
  for (size_t i = 0; i < inputTerms.termNum; i++) {
    const char * ptr1 = inputTerms.termarr[i];
    const char * ptr2 = inputTerms.termarr[i];
    const char * end_ptr = &inputTerms.termarr[i][strlen(inputTerms.termarr[i]) - 1];

    // copy inputTerms.space[i] to output
    outputTerms.space[i] = inputTerms.space[i];

    // allocate memory for outputTerms.termarr[i] with the size of inputTerms.termarr[i]
    outputTerms.termarr[i] = NULL;
    outputTerms.termarr[i] =
        malloc((strlen(inputTerms.termarr[i]) + 1) * sizeof(*outputTerms.termarr[i]));

    while (ptr1 != NULL) {
      // check if the array term have '_'
      ptr1 = strchr(ptr1, '_');
      ptr2 = strrchr(ptr2, '_');

      // if the array have '_'
      if (ptr1 != NULL) {
        // copy term without '_'s
        strncpy(outputTerms.termarr[i], ptr1 + 1, ptr2 - ptr1 - 1);

        // add the null terminator at the end
        outputTerms.termarr[i][ptr2 - ptr1 - 1] = '\0';

        // if the category is not an integer
        if (atoi(outputTerms.termarr[i]) == 0) {
          const char * stringcat = NULL;
          stringcat = chooseWord(outputTerms.termarr[i], cats);

          // replace outputTerms.termarr[i] with stringcat
          strcpy(outputTerms.termarr[i], stringcat);

          // store the word in list struct
          // increment outputTerms.list.num
          outputTerms.list.num++;

          // allocate memory to store the word used
          outputTerms.list.words =
              realloc(outputTerms.list.words,
                      outputTerms.list.num * sizeof(*outputTerms.list.words));
          outputTerms.list.words[outputTerms.list.num - 1] =
              malloc((strlen(stringcat) + 1) *
                     sizeof(*outputTerms.list.words[outputTerms.list.num - 1]));

          // copy stringcat to outputTerms.list.words
          strcpy(outputTerms.list.words[outputTerms.list.num - 1], stringcat);

          // if "-n", then remove
          if (ind == 1) {
            for (size_t k = 0; k < cats->n; k++) {
              for (size_t j = 0; j < cats->arr[k].n_words; j++) {
                // if one of the words in savedres is same as stringcat, reformat cats->arr[k].words
                if (cats->arr[k].words[j] == stringcat) {
                  // delete the same words in words array
                  cats->arr[k].n_words--;
                  free(cats->arr[k].words[j]);
                  cats->arr[k].words[j] = NULL;

                  // make temporary words array to reformat
                  char ** tmpWordsList = NULL;
                  tmpWordsList = malloc(cats->arr[k].n_words * sizeof(*tmpWordsList));

                  // index for tmpWordslist
                  size_t l = 0;
                  for (size_t z = 0; z < cats->arr[k].n_words + 1; z++) {
                    // store words to tmpwordslist if it's not NULL
                    if (cats->arr[k].words[z] != NULL) {
                      tmpWordsList[l] = NULL;
                      tmpWordsList[l] = malloc((strlen(cats->arr[k].words[z]) + 1) *
                                               sizeof(*tmpWordsList[l]));
                      strcpy(tmpWordsList[l], cats->arr[k].words[z]);
                      l++;
                    }
                  }

                  // free the existing old words array
                  for (size_t z = 0; z < cats->arr[k].n_words + 1; z++) {
                    free(cats->arr[k].words[z]);
                  }
                  free(cats->arr[k].words);

                  cats->arr[k].words = NULL;

                  // create new words array without used words
                  cats->arr[k].words =
                      malloc(cats->arr[k].n_words * sizeof(*cats->arr[k].words));
                  for (size_t z = 0; z < cats->arr[k].n_words; z++) {
                    cats->arr[k].words[z] = malloc((strlen(tmpWordsList[z]) + 1) *
                                                   sizeof(*cats->arr[k].words[z]));
                    strcpy(cats->arr[k].words[z], tmpWordsList[z]);
                  }

                  // free tmpwordslist
                  for (size_t z = 0; z < cats->arr[k].n_words; z++) {
                    free(tmpWordsList[z]);
                  }
                  free(tmpWordsList);
                  break;
                }
              }
            }
          }
        }

        // otherwise, if the category is an integer
        // i.e. if it's number such as _1_ or _2_
        else {
          // assign the int to index
          int index = atoi(outputTerms.termarr[i]);

          // allocate the memory for storing it
          outputTerms.termarr[i] =
              realloc(outputTerms.termarr[i],
                      (strlen(outputTerms.list.words[outputTerms.list.num - index]) + 1) *
                          sizeof(*outputTerms.termarr[i]));

          // copy the used words in list to outputTerms.termarr[i]
          strcpy(outputTerms.termarr[i],
                 outputTerms.list.words[outputTerms.list.num - index]);

          //store the words that used
          outputTerms.list.num++;
          outputTerms.list.words =
              realloc(outputTerms.list.words,
                      outputTerms.list.num * sizeof(*outputTerms.list.words));
          outputTerms.list.words[outputTerms.list.num - 1] =
              malloc((strlen(outputTerms.termarr[i]) + 1) *
                     sizeof(*outputTerms.list.words[outputTerms.list.num - 1]));
          strcpy(outputTerms.list.words[outputTerms.list.num - 1],
                 outputTerms.termarr[i]);
        }

        // if the term is the last term of the line
        if (*end_ptr != '_') {
          const char * ptr3 = ptr2 + 1;

          // reallocate momery to append the rest of string
          outputTerms.termarr[i] =
              realloc(outputTerms.termarr[i],
                      (strlen(outputTerms.termarr[i]) + 2 +
                       strlen(ptr3) * sizeof(*outputTerms.termarr[i])));
          // append the rest of string to the name of category
          strcat(outputTerms.termarr[i], ptr3);
        }
        break;
      }

      // if the term does not include '_', just copy input to output
      else {
        strcpy(outputTerms.termarr[i], inputTerms.termarr[i]);
      }
    }
  }

  return outputTerms;
}

prevWords_t cpList(prevWords_t inputlist) {
  // declare outputlist
  prevWords_t outputlist;

  // save inputlist.num to outputlist.num
  outputlist.num = inputlist.num;
  outputlist.words = malloc(outputlist.num * sizeof(*outputlist.words));

  // copy each words to outputlist.words
  for (size_t i = 0; i < outputlist.num; i++) {
    outputlist.words[i] =
        malloc((strlen(inputlist.words[i]) + 1) * sizeof(*outputlist.words[i]));

    strcpy(outputlist.words[i], inputlist.words[i]);
  }
  return outputlist;
}

void printTermInfo(termInfo_t termRes) {
  for (size_t i = 0; i < termRes.termNum; i++) {
    if ((i != termRes.termNum - 1) && (termRes.space[i] == 1)) {
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
  free(termRes.space);
}

void freeList(prevWords_t list) {
  for (size_t i = 0; i < list.num; i++) {
    free(list.words[i]);
  }
  free(list.words);
}

void freeListinTermInfo(termInfo_t termRes) {
  for (size_t i = 0; i < termRes.list.num; i++) {
    free(termRes.list.words[i]);
  }
  free(termRes.list.words);
}

catInfo_t parseLineSemi(char * line) {
  catInfo_t res;
  res.cat = NULL;
  res.name = NULL;

  // counter for checking if line has "cat:name" format
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
    // if there is ':' in line
    while (*ptr1 != '\0') {
      // allocate the memory for res.cat
      res.cat = malloc((ptr1 - ptr2 + 1) * sizeof(*res.cat));

      if (ptr1 != NULL) {
        strncpy(res.cat, ptr2, ptr1 - ptr2);
        // append null terminator at the end of the string res.cat
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
    // append the null terminator at the end of the string res.name
    res.name[edptr - mdptr - 1] = '\0';

    counter++;

    // check if the line has expected format "cat:name"
    if (counter != 2) {
      fprintf(stderr, "Line have an incorrect number of elements\n");
      exit(EXIT_FAILURE);
    }
  }
  return res;
}

// function for storing the first element in savedres
catarray_t storeNewArr(catInfo_t res, catarray_t savedres) {
  // increment the number of category
  savedres.n++;

  savedres.arr = realloc(savedres.arr, savedres.n * sizeof(*savedres.arr));

  // initialize name and n_words
  savedres.arr[savedres.n - 1].name = NULL;
  savedres.arr[savedres.n - 1].n_words = 0;

  savedres.arr[savedres.n - 1].name =
      malloc((strlen(res.cat) + 1) * sizeof(*savedres.arr[savedres.n - 1].name));

  //copy res.cat string to savedres.arr[0].name
  strcpy(savedres.arr[savedres.n - 1].name, res.cat);

  savedres.arr[savedres.n - 1].n_words++;

  // copy res.name to savedres.arr[0].words[0]
  savedres.arr[savedres.n - 1].words = malloc(
      savedres.arr[savedres.n - 1].n_words * sizeof(*savedres.arr[savedres.n - 1].words));

  savedres.arr[savedres.n - 1].words[0] = NULL;
  savedres.arr[savedres.n - 1].words[0] =
      malloc((strlen(res.name) + 1) * sizeof(*savedres.arr[savedres.n - 1].words[0]));
  strcpy(savedres.arr[savedres.n - 1].words[0], res.name);

  return savedres;
}

catarray_t storeRes(catInfo_t res, catarray_t savedres) {
  // count for checking if the res.cat does not exist in savedres.arr
  size_t count = 0;

  // check one arr by one arr to see if there is existing arr for res.cat
  for (size_t i = 0; i < savedres.n; i++) {
    // if res.cat is in savedres.arr
    if (strcmp(savedres.arr[i].name, res.cat) == 0) {
      savedres.arr[i].n_words++;

      savedres.arr[i].words =
          realloc(savedres.arr[i].words,
                  savedres.arr[i].n_words * sizeof(*savedres.arr[i].words));

      savedres.arr[i].words[savedres.arr[i].n_words - 1] =
          malloc((strlen(res.name) + 1) *
                 sizeof(*savedres.arr[i].words[savedres.arr[i].n_words - 1]));

      // store res.name to savedres.arr[i].words
      strcpy(savedres.arr[i].words[savedres.arr[i].n_words - 1], res.name);

      count++;
    }
    count++;
  }

  // if there is no existing res.cat in savedres.arr
  if (count == savedres.n) {
    // make new arr in savedres
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

void checkFileOpen(FILE * catF, FILE * tmpF) {
  if (catF == NULL) {
    fprintf(stderr, "Could not open a file with the categories/words\n");
    exit(EXIT_FAILURE);
  }

  if (tmpF == NULL) {
    fprintf(stderr, "Could not open a story template file\n");
    exit(EXIT_FAILURE);
  }
}

void checkFileClosed(FILE * catF, FILE * tmpF) {
  if (fclose(catF) != 0) {
    fprintf(stderr, "A file with the categories/words fail to close\n");
    exit(EXIT_FAILURE);
  }

  if (fclose(tmpF) != 0) {
    fprintf(stderr, "A file for story template fail to close\n");
    exit(EXIT_FAILURE);
  }
}

catarray_t savedCatfor4(FILE * catF, catarray_t savedcat) {
  char * line1 = NULL;
  size_t sz1 = 0;

  // declare line number counter
  size_t lenNum = 0;

  while (getline(&line1, &sz1, catF) >= 0) {
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

  return savedcat;
}

void cd_underscorefor4(FILE * tmpF, catarray_t savedcat, catarray_t * inputCat, int n) {
  char * line2 = NULL;
  size_t sz2 = 0;

  // declare and initialize prevWordsList
  prevWords_t prevWordsList;
  prevWordsList.words = NULL;
  prevWordsList.num = 0;

  while (getline(&line2, &sz2, tmpF) >= 0) {
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

    if (n == 0) {
      // store result of cd_underscore in termRes2
      termRes2 = cd_underscore(termRes, inputCat, prevWordsList, 0);
    }

    else if (n == 1) {
      //chooseword will not return a word that has already been used
      //should be changed
      termRes2 = cd_underscore(termRes, inputCat, prevWordsList, 1);
    }
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
}
