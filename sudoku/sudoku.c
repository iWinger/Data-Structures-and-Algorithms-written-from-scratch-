#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int solvcount = 0;

bool subMatricies(int input[9][9]){
/* define loop variables, and sum variables, and check */
int i = 0;
int a = 0;
int b = 0;
int c = 0;
int sum = 0;
int check = 0;
bool matcheck = false;
/*what these multiple double-for loops do is ensure that each submatrix
has a sum of 45 successively, because the sum of 1 - 9 is 45. */
for(i = 0; i < 3; i++){
   for(a = 0; a < 3; a++){
   sum = sum + input[i][a];
   if(sum == 45){
   check++;
   }
}
}   
   for(i =0; i < 3; i++){
   for(b = 3; b < 6; b++){
   sum = sum + input[i][b];
  if(sum == 90){
   check++;
   }
   } 	
   }
   for(i = 0; i < 3; i++){
   for(c = 6; c < 9; c++){
   sum = sum + input[i][c];
    if(sum==135){
    check++;
    }
    } 
    }
    
for(i = 3; i < 6; i++){
    for(a=0; a < 3; a++){
    sum = sum + input[i][a];
    if(sum==180){
    check++;
    }
    }
    }
    for(i=3; i < 6; i++){
    for(b=3; b< 6; b++){
    sum = sum + input[i][b];
    if(sum==225){
    check++;
    }
    }
    }
    for(i=3; i < 6; i++){
    for(c=6; c< 9; c++){
    sum = sum + input[i][c];
    if(sum==270){
    check++;
    }
    }
    }

for(i = 6; i < 9; i++){
    for(a=0; a < 3; a++){
    sum = sum + input[i][a];
    if(sum == 315){
    check++;
    }
    }
    }
  for(i=6;i<9;i++){
    for(b = 3; b< 6; b++){
    sum = sum + input[i][b];
    if(sum == 360){  
    check++;
    }
    }
    }
    for(i=6; i<9; i++){
    for(c = 6; c< 9; c++){
    sum = sum + input[i][c];
    if(sum == 405){
    check++;
    }
    }
    }
    
/*check variable to make sure every submatrix is 1 - 9 */
if(check == 9){
matcheck = true;}
return matcheck;
}

bool columnsolver(int input[9][9]){
/* make sure that the first number of the column isn't repeated elsewhere in that column */
bool colcheck = false;
int ssize = 9;
int count = 0;
int b = 0;
int c = 0;
for ( b = 0; b < ssize; b++){
for ( c = 0; c < ssize; c++){
if(input[b][0] != input[c][b])
count++;
}
}
/* count is 72 because 81 - 9 (the 9 coming from each starting number of the column ) */
if(count == 72){
colcheck = true;
}
return colcheck;
}

bool rowsolver(int input[9][9]){
/* same as colsolver, but with rows */
bool rowcheck = false;
int ssize = 9;
int b = 0;
int c = 0;
int count = 0;

for(b=0; b< ssize; b++){
for(c=0; c< ssize; c++){
if(input[0][b] != input[b][c])
count++;
}
}

if(count == 72){
 rowcheck = true;
}
  return rowcheck;
}

bool solvability(int input[9][9], int sCount){
/* looping variables to store, and an almost complete sudoku puzzle is either 1 or 2 missing.
Therefore, arr[4] comes from 4 indices, the first 2 from 1st missing and the last 2 from the 2nd missing. */
int n = 1;
int m1 = 1;
int m2 = 1;
int arrcount = 0;
bool solv = false;
int x,y;
int arr[4];
/* -16 is the ascii value for space, and this stores the indices. Mainly, this function is used to test the solvability for 
one missing number -- checking each value to see if any number can make the solution */
for(x=0;x<9;x++){
for(y=0;y<9;y++){
if(input[x][y] == -16){
arr[arrcount] = x;
arr[arrcount+1] = y;
arrcount = arrcount + 2;
while(n<=9){
input[x][y] = n;
if(sCount == 1){
if(rowsolver(input)&& columnsolver(input) && subMatricies(input)){
solv = true;
return solv;
}
}
n++;
}
}
}
}

/* sCount is the solvability count, or how many spaces are these. */
if(sCount == 2){
/* indices */
int i0 = arr[0];
int i1 = arr[1];
int i2 = arr[2];
int i3 = arr[3];
/* putting every possible combination of values for those 2 missing spaces */
while(m1<=9){
for(m2=1; m2<=9; m2++){
input[i0][i1] = m1;
input[i2][i3] = m2;
if(rowsolver(input)&&columnsolver(input)&& subMatricies(input)){
solv = true;
}
}
m1++;
}
}
return solv;
}

int main(int argc, char* argv[]){
int sudoku[9][9];
/*char buf[100];*/
FILE *fp = fopen(argv[1], "r");
int i,j;
if(fp==0){
printf("%s", "error");
return 1;
}
unsigned ch;
/* makes sure we get all the digits and this is ensured because sudoku only has numbers 1 - 9*/
for(i = 0; i < 9; i++){
for(j = 0; j < 9; j++){ 
sudoku[i][j] = ((ch = fgetc(fp)) - '0');
}
ch = fgetc(fp);
} 

int a,b;
/* find the spaces */
for(a=0;a<9;a++){
for(b=0;b<9;b++){
if(sudoku[a][b] == -16)
solvcount++;
}
}
/* if all numbers of sudoku are filled up already, then no need for solvability count */
if(solvcount == 0){
if(rowsolver(sudoku) && columnsolver(sudoku) && subMatricies(sudoku))
printf("%s\n", "correct");
else
printf("%s\n", "incorrect");
}
else{
if(solvability(sudoku, solvcount))
printf("%s\n", "solvable");
else
printf("%s\n", "unsolvable");
}

fclose(fp);
return 0;
}


