#include "rand_story.h"

#include <stdio.h>
#include <stdlib.h>

const char * chooseWord(char * category, catarray_t * cats) {
  // if the category dose not have any words, the function will exit the program with a failure status
  if (category == NULL) {
    fprintf(stderr, "category does not have any words");
    exit(EXIT_FAILURE);
  }

  char * cat = "cat";

  if (cats == NULL) {
    return cat;
  }

  else {
    for (size_t i = 0; i < cats->n; i++) {
      if (cats->arr[i].name == category) {
        // check if it's right string to point
        return cats->arr[i].name;
      }
    }
    fprintf(stderr, "The requested category does not exist in cats");
    exit(EXIT_FAILURE);
  }
}
