#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  // commands should be either 3 or 4 (either without "-n" or with it)
  if ((argc != 3) && (argc != 4)) {
    fprintf(stderr, "Incorrect Commands\n");
    exit(EXIT_FAILURE);
  }

  // In case, with no "-n", it can behave same as step3
  if (argc == 3) {
    FILE * cat_words = fopen(argv[1], "r");
    FILE * st_tmpl = fopen(argv[2], "r");
    int _n = 0;  // index for "-n"

    // check if files are opened correctly
    checkFileOpen(cat_words, st_tmpl);

    // catarray_t struct for saved categories/words
    catarray_t savedcat;
    savedcat.arr = NULL;
    savedcat.n = 0;

    savedcat = savedCatfor4(cat_words, savedcat);

    // get a pointer for previously saved categories/words struct
    catarray_t * inputCat = NULL;
    inputCat = &savedcat;

    // change categories with underscores with random chosen words
    cd_underscorefor4(st_tmpl, savedcat, inputCat, _n);

    // check if the files are  closed correctly
    checkFileClosed(cat_words, st_tmpl);
  }

  // in case with "-n" command, it doesn't reuse words that already used
  else if (argc == 4) {
    FILE * cat_words = fopen(argv[2], "r");
    FILE * st_tmpl = fopen(argv[3], "r");
    int _n = 1;  // index for "-n"

    // check if the file is opened correctly
    checkFileOpen(cat_words, st_tmpl);

    // catarray_t struct for saved categories/words
    catarray_t savedcat;
    savedcat.arr = NULL;
    savedcat.n = 0;

    savedcat = savedCatfor4(cat_words, savedcat);

    // get a pointer for previously saved categories/words
    catarray_t * inputCat = NULL;
    inputCat = &savedcat;

    // change categories with underscore with random chosen words with not repeating used words
    cd_underscorefor4(st_tmpl, savedcat, inputCat, _n);

    // check if the files are closed correctly
    checkFileClosed(cat_words, st_tmpl);
  }
}
