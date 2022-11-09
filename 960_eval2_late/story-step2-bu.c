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

  /*
  catarray_t savedres2;
  savedres2.arr = NULL;
  savedres2.n = 0;
  */
  char * line = NULL;
  size_t sz = 0;
  size_t lenNum = 0;

  catInfo_t res;
  res.cat = NULL;
  res.name = NULL;

  while (getline(&line, &sz, f) >= 0) {
    lenNum++;
    /*
    catInfo_t res;

    res.cat = NULL;
    res.name = NULL;
    */

    res = parseLineSemi(line);
    /*
    catarray_t savedres;
    savedres.arr = NULL;
    savedres.n = 0;

    catarray_t savedres2;
    savedres2.arr = NULL;
    savedres2.n = 0;
    */
    if (lenNum == 1) {
      savedres = storeNewArr(res, savedres);

      //      finalSavedRes = arrDeepCopy(savedres);
      /*
      finalSavedRes.arr = malloc(finalSavedRes.n * sizeof(*finalSavedRes.arr));
      for (size_t i = 0; i < finalSavedRes.n; i++) {
	finalSavedRes.arr[i] = savedres.arr[i];
	}*/
      //freeSavedRes(savedres);
      //free(res.cat);
      //free(res.name);
    }
    else {
      //savedres2 = arrDeepCopy(finalSavedRes);
      savedres = storeRes(res, savedres);
      //finalSavedRes = arrDeepCopy(savedres2);
      //freeSavedRes(savedres2);
      //free(res.cat);
      //free(res.name);
    }
  }
  free(line);
  //free(res.cat);
  //free(res.name);
  for (size_t i = 0; i < savedres.n; i++) {
    printf("%s:\n", savedres.arr[i].name);
    for (size_t j = 0; j < savedres.arr[i].n_words; j++) {
      printf("  %s\n", savedres.arr[i].words[j]);
    }
  }
  /*
  for (size_t i = 0; i < savedres.n; i++) {
    free(savedres.arr[i].name);
    for (size_t j = 0; j < savedres.arr[i].n_words; j++) {
      free(savedres.arr[i].words[j]);
    }
  }
  */
  //freeSavedRes(finalSavedRes);
  freeSavedRes(savedres);
  if (fclose(f) != 0) {
    fprintf(stderr, "File closed failure");
  }
}
