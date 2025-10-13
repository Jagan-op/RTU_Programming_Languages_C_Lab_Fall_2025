#include <stdio.h>
#include <stdlib.h>

#define FILENAME "data.txt"
#define MAX_LINE_LENGTH 256
#define NUM_LINES 2

int main() {
  FILE *fp;
  char buffer[MAX_LINE_LENGTH];
  const char *lines[NUM_LINES] = {"Hello, file I/O in C!\n",
                                  "The world shall know pain this the title of my new novel \n"};

  // Writing to the file
  printf("Writing lines to %s...\n", FILENAME);
  fp = fopen(FILENAME, "w");
  if (fp == NULL) {
    perror("Error opening file for writing");
    return 1;
  }
  for (int i = 0; i < NUM_LINES; ++i) {
    if (fprintf(fp, "%s", lines[i]) < 0) {
      perror("Error writing to file");
      fclose(fp);
      return 1;
    }
  }
  fclose(fp);

  // Reading from the file
  printf("Reading contents:\n");
  fp = fopen(FILENAME, "r");
  if (fp == NULL) {
    perror("Error opening file for reading");
    return 1;
  }
  while (fgets(buffer, MAX_LINE_LENGTH, fp) != NULL) {
    printf("%s", buffer);
  }
  fclose(fp);

  return 0;
}
