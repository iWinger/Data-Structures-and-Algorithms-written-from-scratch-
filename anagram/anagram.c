#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
/* swapping using pointers */
void swap(char * a, char * b) {

    char temp = * a;

    * a = * b;

    * b = temp;

  }

int main(int argc, char * argv[]) {

  int i;

  int j;

  int charLength = (strlen(argv[1]) - 1);

  /* two for loops to measure the last character against every preceding character, and this goes on until the beginning char
  this ensures alphabetical order */
  for (j = charLength; j > 0; j--) {

    for (i = charLength; i > 0; i--) {

      if (argv[1][i] < argv[1][i - 1]) {

        /* this SWAPS by giving the address */
        swap( & argv[1][i], & argv[1][i - 1]);

      }

    }

  }

  printf("%s\n", argv[1]);

  return 0;
}
