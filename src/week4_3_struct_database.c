
#include <stdio.h>   
#include <stdlib.h>  // for malloc and free

// Define the maximum length for a student's name
#define NAME_LEN 100

// Define the Student structure to hold student data
struct Student {
  int id;               // Student ID
  char name[NAME_LEN];  // Student name
  float grade;          // Student grade
};

int main() {
  int n;

  // Prompt the user for the number of students
  printf("Enter number of students: ");
  if (scanf("%d", &n) != 1 || n <= 0) {
    // Check for valid input
    printf("Invalid number.\n");
    return 1;
  }

  // Dynamically allocate memory for n Student records
  struct Student *students = malloc(n * sizeof(struct Student));
  if (!students) {
    // Check if memory allocation was successful
    printf("Memory allocation failed.\n");
    return 1;
  }

  
  for (int i = 0; i < n; ++i) {// Read each student's data from the user
    printf("Enter data for student %d: ", i + 1);
    if (scanf("%s %d %f", students[i].name, &students[i].id,// Read name (no spaces), ID, and grade
              &students[i].grade) != 3) {
      printf("Invalid input.\n");
      free(students);  // Free memory before exit on error
      return 1;
    }        
  }

  // Print all student records in a formatted table
  printf("\n%-6s %-12s %-5s\n", "ID", "Name", "Grade");
  for (int i = 0; i < n; ++i) {
    printf("%-6d %-12s %-5.1f\n", students[i].id, students[i].name,
           students[i].grade);
  }

  // Free the dynamically allocated memory before program exit
  free(students);
  return 0;
}
