#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void sort_one_file(void * f) {
  char ** lines = NULL;
  char * line = NULL;
  size_t sz = 0;
  size_t i = 0;
  while (getline(&line, &sz, f) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = line;
    line = NULL;
    i++;
  }

  free(line);
  sortData(lines, i);
  for (size_t j = 0; j < i; j++) {
    printf("%s", lines[j]);
    free(lines[j]);
  }
  free(lines);
}

void sort_more_than_one_file(int argc, char ** argv) {
  for (int i = 0; i < argc - 1; i++) {
    FILE * f = fopen(argv[i + 1], "r");
    if (f == NULL) {
      perror("Could not open file");
      exit(EXIT_FAILURE);
    }
    sort_one_file(f);

    if (fclose(f) != 0) {
      perror("Failed to close the input file");
      exit(EXIT_FAILURE);
    }
  }
}
int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    FILE * f = fopen(argv[1], "r");
    sort_one_file(f);
  }

  else {
    sort_more_than_one_file(argc, argv);
  }
  return EXIT_SUCCESS;
}
