#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rot_matrix(FILE * f) {
  char rot_matrix[10][10] = {{0}};
  char x[12] = {0};
  for (int i = 0; i < 10; i++) {
    if ((fgets(x, 12, f) != NULL)) {
      if (strchr(x, '\n') == NULL) {
        perror("more than 10 characters\n");
        exit(EXIT_FAILURE);
      }

      if (x[10] != '\n') {
        perror("incorrect number of char\n");
        exit(EXIT_FAILURE);
      }

      if (x[0] == '\n') {
        perror("less than 10 rows\n");
        exit(EXIT_FAILURE);
      }

      else {
        for (int j = 0; j < 10; j++) {
          if (x[j] == '\n') {
            perror("incorrect number of char\n");
            exit(EXIT_FAILURE);
          }

          else {
            rot_matrix[j][9 - i] = x[j];
          }
        }
      }
    }
    else {
      perror("less than 10 rows\n");
      exit(EXIT_FAILURE);
    }
  }

  if (fgets(x, 12, f) != NULL) {
    perror("more than 10 rows\n");
    exit(EXIT_FAILURE);
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
