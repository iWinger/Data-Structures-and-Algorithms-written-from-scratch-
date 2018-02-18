#include <stdio.h> 
#include <stdlib.h>
  /* defining the matrix size, and exp variables used to keep track of which method to put in */
  int msize;
int exp1;
int countexp = 2;
void printMatrix(int *arr[]) {
    int a1;
    int a2;
    for (a1 = 0; a1 < msize; a1++) {
      for (a2 = 0; a2 < msize; a2++) {
        printf("%d", arr[a1][a2]);
        if (a2 != msize - 1) {
          printf(" ");
        }
      }
      printf("\n");
    }
  }
  /* the next 2 methods are almost exactly the same, the reasoning behind this is to method call each other,
  one is for an even exponent, one is for an odd. */

void expMatrix(int *input[], int *dupinput[]) {
  /*provide a prototype to call back to */
  void changeMatrix(int *arr[], int *duparr[]);
  int b;
  int c;
  int d;
  int sum = 0;
  int k;
  int** temp = (int**) malloc(msize * sizeof(int*));
  for (k = 0; k < msize; k++) {
    temp[k] = (int*) malloc(msize * sizeof(int));
  }
  /* matrix multiplication -- first multiply the corresponding elements of respective columns and rows and add */
  for (b = 0; b < msize; b++) {
    for (c = 0; c < msize; c++) {
      for (d = 0; d < msize; d++) {
        sum = sum + (dupinput[b][d] * input[d][c]);
      }
      temp[b][c] = sum;
      sum = 0;
    }
  }
  /* if exponent is 2, then print the function, otherwise, use the resulting matrix and multiply it in another function */
  if (countexp == exp1) {
    printMatrix(temp);
    return;
  } else {
    countexp++;
    changeMatrix(input, temp);
  }
}
void changeMatrix(int * input[], int * dupinput[]) {
  /*loop variables and sum to add */
  int b;
  int c;
  int d;
  int sum = 0;
  int k;
  if (exp1 == 1) {
    printMatrix(input);
    return;
  }

  int** temp = (int**) malloc(msize * sizeof(int*));
  for (k = 0; k < msize; k++) {
    temp[k] = (int*) malloc(msize * sizeof(int));
  }

  for (b = 0; b < msize; b++) {
    for (c = 0; c < msize; c++) { /* find the sum for the rest of rows and columns */
      for (d = 0; d < msize; d++) { /* find the sum for 1 row of input and msize columns */
        sum = sum + (dupinput[b][d] * input[d][c]);
      }
      temp[b][c] = sum;
      sum = 0;
    }
  }

  if (countexp == exp1) {
    printMatrix(temp);
    return;
  } else {
    countexp++;
    expMatrix(input, temp);
  }
}

int main(int argc, char * argv[]) {
  FILE * fp = fopen(argv[1], "r");
  int n = 0;
  int d;
  int d2;
  if (fp == 0) {
    printf("%s", "error");
    return 1;
  }
  /* what i am doing here is scanning the first line separately for the matrix size,
  allocating memory, and getting 2 exactly similar matricies */
  fscanf(fp, "%d", & msize);
  int** matrix = (int**) malloc(msize * sizeof(int*));
  for (d = 0; d < msize; d++) {
    matrix[d] = malloc(msize * sizeof(int));
  }
  int** dupmatrix = (int**) malloc(msize * sizeof(int*));
  for (d2 = 0; d2 < msize; d2++) {
    dupmatrix[d2] = malloc(msize * sizeof(int));
  }
  /* filling the matricies up with values */
  while (n < msize) {
    int num;
    int i;
    for (i = 0; i < msize; i++) {
      fscanf(fp, "%d", &num);
      matrix[n][i] = num;
      dupmatrix[n][i] = num;
    }
    n++;
  }
  /* scanning in the last line for the exponent*/
  fscanf(fp, "%d", &exp1);
  fclose(fp);
  /* if the exponent is zero, fill all the values of matrix with ones. */
  if (exp1 == 0) {
    int a, b;
    for (a = 0; a < msize; a++) {
      for (b = 0; b < msize; b++) {
        matrix[a][b] = 1;
        printf("%d ", matrix[a][b]);
      }
      printf("\n");
    }
  } else {
    changeMatrix(matrix, dupmatrix);
  }
  return 0;
}
