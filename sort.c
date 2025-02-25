#include "types.h"
#include "stat.h"
#include "user.h"

// implementing the bubble sort algorithm, added checking for sort completion for better efficiency --Mostafa
void bubble_sort(int arr[], int n) {
  int swapped = 0;
  int i, j, temp;

  for (i = 0; i < n - 1; i++) {
    swapped = 0;
    for (j = 0; j < n - 1 - i; j++) {
      if (arr[j] > arr[j + 1]) {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
        swapped = 1;
      }
    }
    if (swapped == 0)
      break;
  }
}

// implementing this function to handle negative numbers as inputs. --Mostafa
// The regular atoi function doesnt handle this by default  --Mostafa


// Prints the array in sorted order --Mostafa
void printArr(int arr[], int n) {
    printf(1, "Sorted Array: ");
    for (int i = 0; i < n; i++) {
        printf(1, "%d ", arr[i]);
    }
    printf(1, "\n");
}

// The main function is only compiled if LIB_SORT is not defined.

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf(1, "Incorrect Usage\n");
        printf(1, "Usage: %s value1 value2 value3 ...\n", argv[0]);
        exit();
    }

    int numbersC = argc - 1;
    int numbers[numbersC];
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--") == 0) {
            continue;
        }
        numbers[i - 1] = atoi(argv[i]);
    }
    bubble_sort(numbers, numbersC);
    printArr(numbers, numbersC);
    exit();
}