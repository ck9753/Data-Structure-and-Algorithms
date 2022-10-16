#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  counts->countArr = NULL;
  counts->countSize = 0;
  counts->unknownSize = 0;

  return counts;
}

void newStringToArray(counts_t * c, const char * name) {
  c->countSize++;
  c->countArr = realloc(c->countArr, c->countSize * sizeof(*c->countArr));
  c->countArr[c->countSize - 1] = malloc(sizeof(*c->countArr[c->countSize - 1]));
  c->countArr[c->countSize - 1]->string = strdup(name);
  c->countArr[c->countSize - 1]->countString = 1;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  size_t new = 1;
  if (name != NULL) {
    for (size_t i = 0; i < c->countSize; i++) {
      if (strcmp(c->countArr[i]->string, name) == 0) {
        new = 0;
        c->countArr[i]->countString++;
        break;
      }
    }
    if (new) {
      newStringToArray(c, name);
    }
  }
  else {
    c->unknownSize++;
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->countSize; i++) {
    fprintf(outFile, "%s: %zd\n", c->countArr[i]->string, c->countArr[i]->countString);
  }
  if (c->unknownSize != 0) {
    fprintf(outFile, "<unknown> : %zd\n", c->unknownSize);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->countSize; i++) {
    free(c->countArr[i]->string);
    free(c->countArr[i]);
  }
  free(c->countArr);
  free(c);
}
