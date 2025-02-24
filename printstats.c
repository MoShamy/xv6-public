// user/printstats.c
#include "types.h"
#include "stat.h"
#include "user.h"


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


int custom_atoi(const char *s) {
  int n = 0;
  int sign = 1;

  if (*s == '-') {
      sign = -1;
      s++;
  }

  while ('0' <= *s && *s <= '9') { // converting string to int, taken from the regular atoi function  --Mostafa
      n = n * 10 + (*s - '0'); // ascii conversion
      s++;
  }

  return sign * n;
}


// Since xv6's printf doesn't support %f, we split the double into integer and fractional parts.
void printDouble(char *label, double value) {
  int intpart = (int)value;
  int frac = (int)((value - intpart) * 10);
  if(frac < 0)
    frac = -frac;
  printf(1, "%s: %d.%d\n", label, intpart, frac);
}

int main(int argc, char *argv[]) {
  if(argc < 2){
    printf(2, "Usage: printstats num1 num2 ...\n");
    exit();
  }
  
  int n = argc - 1;
  
  // Allocate memory for the numbers array
  int *nums = malloc(n * sizeof(int));
  if(nums == 0){
    printf(2, "Memory allocation failed\n");
    exit();
  }
  
  // Convert command-line arguments to integers using custom_atoi (handles negatives) --Mostafa
  for(int i = 0; i < n; i++){
    nums[i] = custom_atoi(argv[i+1]);
  }
  
  // Calculate min, max and sum for average
  int min = nums[0], max = nums[0], sum = 0;
  for(int i = 0; i < n; i++){
    if(nums[i] < min)
      min = nums[i];
    if(nums[i] > max)
      max = nums[i];
    sum += nums[i];
  }
  double avg = (double)sum / n;
  
  // Calculate variance correctly using floating-point arithmetic
  double variance = 0;
  for(int i = 0; i < n; i++){
    double diff = nums[i] - avg;
    variance += diff * diff;
  }
  variance /= n;
  double stddev = variance;  // stddev^2 is stored in stddev
  
  // Allocate memory for a copy of the array to compute the median
  int *sorted = malloc(n * sizeof(int));
  if(sorted == 0){
    printf(2, "Memory allocation failed\n");
    free(nums);
    exit();
  }
  for(int i = 0; i < n; i++){
    sorted[i] = nums[i];
  }
  
  // Use the external bubble_sort function from sort.c
  bubble_sort(sorted, n);
  
  double median;
  if(n % 2 == 0)
    median = (sorted[n/2 - 1] + sorted[n/2]) / 2.0;
  else
    median = sorted[n/2];
  
  // Print the computed statistics, using floating-point values where needed.
  printf(1, "Count: %d\n", n);
  printDouble("Average", avg);
  printDouble("Variance (stddev^2)", stddev);
  printDouble("Median", median);
  printf(1, "Min: %d\n", min);
  printf(1, "Max: %d\n", max);
  
  free(nums);
  free(sorted);
  exit();
}
