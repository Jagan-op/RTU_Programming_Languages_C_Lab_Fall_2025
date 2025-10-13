#include <stdio.h>
#include <stdlib.h>

#define FILENAME "student.txt"
#define NAME_LEN 100

typedef struct {
  char name[NAME_LEN];
  int age;
  float gpa;
} Student;

int save_student(const char *filename, const Student *s) {
  FILE *fp = fopen(filename, "w");
  if (fp == NULL) {
    perror("Error opening file for writing");
    return 0;
  }
  fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa);
  fclose(fp);
  return 1;
}

int load_student(const char *filename, Student *s) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    perror("Error opening file for reading");
    return 0;
  }
  if (fscanf(fp, "%99s %d %f", s->name, &s->age, &s->gpa) != 3) {
    fprintf(stderr, "Error reading student data from file.\n");
    fclose(fp);
    return 0;
  }
  fclose(fp);
  return 1;
}

int main(void) {
  Student s1 = {"Tony", 30, 4.75f};
  Student s2;

  printf("Saving student to file...\n");
  if (!save_student(FILENAME, &s1)) {
    return 1;
  }

  printf("Loading student from file...\n");
  if (!load_student(FILENAME, &s2)) {
    return 1;
  }

  printf("Loaded student: %s, %d, GPA %.2f\n", s2.name, s2.age, s2.gpa);
  return 0;
}
