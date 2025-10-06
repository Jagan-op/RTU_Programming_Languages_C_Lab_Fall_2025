
#include <stdio.h>
#include <string.h>


struct Student {
  char name[50];  // array to store the student's name
  int id;         // integer to store the student's ID
  float grade;    // float to store the student's grade
};

int main() {
  // Declare two variables of type struct Student
  struct Student student1, student2;// declaring two varable 

  // Assign values to student1 fields
  // Use strcpy to copy a string into the name field
  strcpy(student1.name, "Alice Smith");
  student1.id = 1001;      // Set student1's ID
  student1.grade = 89.5f;  // Set student1's grade

  // Assign values to student2 fields
  strcpy(student2.name, "Bob Johnson");
  student2.id = 1002;      // Set student2's ID
  student2.grade = 92.0f;  // Set student2's grade

  // Print student1's information in a formatted way
  printf("Student 1 Information:\n");
  printf("Name : %s\n", student1.name);
  printf("ID   : %d\n", student1.id);
  printf("Grade: %.2f\n\n", student1.grade);

  // Print student2's information in a formatted way
  printf("Student 2 Information:\n");
  printf("Name : %s\n", student2.name);
  printf("ID   : %d\n", student2.id);
  printf("Grade: %.2f\n", student2.grade);

  // Indicate successful program termination
  return 0;
}
