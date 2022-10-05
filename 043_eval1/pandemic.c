#include "pandemic.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

country_t parseLine(char * line) {
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;

  // make char array for result name and population
  char res_name[64] = {0};
  char res_population[64] = {0};

  size_t counter = 0;

  // take input line to use pointers
  const char * ptr1 = line;
  const char * ptr2 = line;
  const char * edptr = line;  //end pointer
  const char * mdptr = line;  //middle pointer

  // check if the line is empty
  if ((line == NULL) || (strlen(line) == 0)) {
    perror("Line is empty\n");
    exit(EXIT_FAILURE);
  }

  // check if the line does not have string separated by comma
  else if (strchr(line, ',') == NULL) {
    perror("Line doesn't include comma(,)\n");
    exit(EXIT_FAILURE);
  }

  else {
    while (*ptr1 != '\0') {
      ptr1 = strchr(ptr1, ',');

      if (ptr1 != NULL) {
        // parse result name using two pointer's location difference
        strncpy(res_name, ptr2, ptr1 - ptr2);
        ptr1++;       //point to the first letter of next token
        ptr2 = ptr1;  // update ptr2 to ptr1 location

        counter++;  // increment the counter of the elements
      }

      else {
        break;  // if ptr is reaching to the end, get out of the loop
      }
    }

    edptr = strchr(line, '\0');  // end pointer that points to the end of the line
    mdptr = strchr(line, ',');   // middle pointer that points to the location of comma

    strncpy(
        res_population,
        mdptr + 1,
        edptr - mdptr -
            1);  // take result population using location difference between edptr and mdptr
    counter++;  //  increment the counter of the elements after getting population string

    // check if the line only have 2 elements, name and population
    if (counter != 2) {
      perror("Line have an incorrect number of elements\n");
      exit(EXIT_FAILURE);
    }

    else {
      // take result name and pass it to name of the answer
      strcpy(ans.name, res_name);
      // take result population, change string to integer, and pass it to population of the answer
      ans.population = atoi(res_population);
    }
  }
  return ans;
}
void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  unsigned sum_data[3000] = {0};  // why sum_data[n_days]; not working

  for (size_t i = 0; i < n_days - 6; i++) {
    for (size_t j = i; j < i + 7; j++) {
      sum_data[i] += data[j];
    }
    avg[i] = (double)sum_data[i] / 7;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  unsigned sum_data[3000] = {0};

  for (size_t i = 0; i < n_days; i++) {
    for (size_t j = 0; j < i + 1; j++) {
      sum_data[i] += data[j];
    }
    cum[i] = (double)(sum_data[i] * 100000) / pop;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  unsigned max_case = 0;
  //char * country_name;
  char * max_country_name;

  for (size_t i = 0; i < n_countries; i++) {
    //country_name = countries[i].name;
    for (size_t j = 0; j < n_days; j++) {
      if (data[i][j] > max_case) {
        max_case = data[i][j];
        max_country_name = countries[i].name;
      }
    }
  }
  printf("%s has the most daily cases with %u\n", max_country_name, max_case);
}
