#include <stdio.h>
#include <stdlib.h>

int main() {
  int n, i, sum = 0;
  int *arr = NULL;
  double average;

  printf("Enter the number of elements: ");// asking the user how integers want to store 
  if (scanf("%d", &n) != 1 || n <= 0) {// in this loop we checking that given input is postive integer
    printf("Invalid input. Exiting.\n");
    return 1;
  }

  arr = (int *)malloc(n * sizeof(int)); //in this line we are allocating memory for integers  
  if (arr == NULL) { // in this loop we are checking the allcation was successful
    printf("Memory allocation failed. Exiting.\n");
    return 1;
  }

  printf("Enter %d integers:\n", n);
  for (i = 0; i < n; i++) { // using for loop that to enter each element 
    printf("Element %d: ", i + 1);
    if (scanf("%d", &arr[i]) != 1) {
      printf("Invalid input. Exiting.\n");
      free(arr);
      return 1;
    }
    sum += arr[i];
  }

  average = (double)sum / n;// calculating avg
  printf("\nSum: %d\n", sum);
  printf("Average: %.2f\n", average);

  free(arr);
  return 0;
}
