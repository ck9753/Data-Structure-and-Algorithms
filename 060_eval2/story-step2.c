#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Incorrect Commands\n");
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[1], "r");

  if (f == NULL) {
    fprintf(stderr, "Could not open file\n");
    exit(EXIT_FAILURE);
  }

  catarray_t savedres;
  savedres.arr = NULL;
  savedres.n = 0;

  char * line = NULL;
  size_t sz = 0;
  size_t lenNum = 0;
  while (getline(&line, &sz, f) >= 0) {
    lenNum++;
    catInfo_t res;

    res.cat = NULL;
    res.name = NULL;

    res = parseLineSemi(line);

    if (lenNum == 1) {
      savedres = storeNewArr(res, savedres);
    }
    else {
      savedres = storeRes(res, savedres);
    }
  }

  for (size_t i = 0; i < savedres.n; i++) {
    printf("%s:\n", savedres.arr[i].name);
    for (size_t j = 0; j < savedres.arr[i].n_words; j++) {
      printf("  %s", savedres.arr[i].words[j]);
    }
  }
}
