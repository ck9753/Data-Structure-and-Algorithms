#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if ((argc != 3) && (argc != 4)) {
    fprintf(stderr, "Incorrect Commands\n");
    exit(EXIT_FAILURE);
  }

  if (argc == 3) {
    FILE * cat_words = fopen(argv[1], "r");
    FILE * st_tmpl = fopen(argv[2], "r");
    int _n = 0;
    checkFileOpen(cat_words, st_tmpl);

    catarray_t savedcat;
    savedcat.arr = NULL;
    savedcat.n = 0;

    savedcat = savedCatfor4(cat_words, savedcat);

    catarray_t * inputCat = &savedcat;

    cd_underscorefor4(st_tmpl, savedcat, inputCat, _n);

    checkFileClosed(cat_words, st_tmpl);
  }

  else if (argc == 4) {
    FILE * cat_words = fopen(argv[2], "r");
    FILE * st_tmpl = fopen(argv[3], "r");
    int _n = 1;
    checkFileOpen(cat_words, st_tmpl);

    catarray_t savedcat;
    savedcat.arr = NULL;
    savedcat.n = 0;

    savedcat = savedCatfor4(cat_words, savedcat);

    catarray_t * inputCat = &savedcat;

    cd_underscorefor4(st_tmpl, savedcat, inputCat, _n);

    checkFileClosed(cat_words, st_tmpl);
  }
}
