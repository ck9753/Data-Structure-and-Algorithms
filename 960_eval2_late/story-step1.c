
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

  char * line = NULL;
  size_t sz = 0;

  while (getline(&line, &sz, f) >= 0) {
    termInfo_t termRes;
    termRes.termarr = NULL;
    termRes.termNum = 0;
    termRes = parseTerm(line);

    termInfo_t termRes2;
    termRes2.termarr = NULL;
    termRes2.termNum = 0;
    termRes2 = cdCatToWord(termRes, NULL);

    freeTermInfo(termRes);
    printTermInfo(termRes2);

    freeTermInfo(termRes2);
  }
  free(line);

  if (fclose(f) != 0) {
    fprintf(stderr, "File closed failure");
    exit(EXIT_FAILURE);
  }
}
