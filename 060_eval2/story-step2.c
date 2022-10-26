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

  while (getline(&line, &sz, f) >= 0) {
    catInfo_t res;

    res.cat = NULL;
    res.name = NULL;

    res = parseLineSemi(line);
    //printf("%s", res.cat);
    //printf("%s", res.name);

    savedres.n++;

    savedres.arr = realloc(savedres.arr, savedres.n * sizeof(*savedres.arr));
    savedres.arr[savedres.n].name = malloc(sizeof(*savedres.arr[savedres.n].name));
    savedres.arr->name = res.cat;
    savedres.arr->n_words++;
    //savedres.arr->words[savedres.arr->n_words]
  }
}
