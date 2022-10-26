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
  //ssize_t len = 0;

  //termInfo_t termRes;
  //termRes.termarr = NULL;
  //termRes.termNum = 0;

  while (getline(&line, &sz, f) >= 0) {
    termInfo_t termRes;
    termRes.termarr = NULL;
    termRes.termNum = 0;
    termRes = parseTerm(line);

    termRes = rmUnderScore(termRes);

    for (size_t i = 0; i < termRes.termNum; i++) {
      /*      if ((strcmp(termRes.termarr[i], "cat") == 0) && (i == termRes.termNum - 1)) {
        printf("%s.\n", termRes.termarr[i]);
      }
      else {*/
      printf("%s ", termRes.termarr[i]);
    }
  }
}
