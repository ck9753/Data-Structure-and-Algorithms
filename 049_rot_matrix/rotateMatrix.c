#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void rot_matrix(FILE * f) {
  char rot_matrix[10][10] = {{0}};
  char x[12] = {0};
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      rot_matrix[j][9 - i] = x[j];
    }
  }
  for (int y = 0; y < 10; y++) {
    for (int z = 0; z < 10; z++) {
      printf("%c", rot_matrix[y][z]);
    }
    printf("%c", '\n');
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rot_matrix inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");

  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  rot_matrix(f);

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
