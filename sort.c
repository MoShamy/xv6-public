#include "types.h"
#include "stat.h"
#include "user.h"
    
 //passing command line arguments 
   
 
 void bubble_sort(int arr[], int n) {
  int i, j, temp;
  for (i = 0; i < n - 1; i++) {
      for (j = 0; j < n - i - 1; j++) {
          if (arr[j] > arr[j + 1]) {
              temp = arr[j];
              arr[j] = arr[j + 1];
              arr[j + 1] = temp;
          }
      }
  }
}

void printArr(int arr[], int n){
  printf(1,"Sorted Array:");
  int i;

  for(i=0;i<n;i++){
    printf(1,"%d ",arr[i]);
  }
  printf(1,"\n");
}

int main(int argc, char *argv[]) 
{ 
  if(argc<2){
    printf(1,"Please enter atleast 2 numbers");
  }
  int numbersC = argc-1;

  int numbers[numbersC];

  for (int i = 1; i < argc; i++) {
    numbers[i - 1] = atoi(argv[i]);
}



  bubble_sort(numbers,numbersC);

  printArr(numbers,numbersC);

  exit(); 
} 