#include <stdio.h> 
#include <ctype.h>

  int main(int argc,
    const char * argv[]) {
    int first = 1;
    int second = 0;
    /* outer loop to scan in the number of strings or arguments*/
    while (first <= argc - 1) {
      /*inner loop to uppercase every character */
      while (argv[first][second] != 0) {
        char c = argv[first][second];
        putchar(toupper(c));
        second++;
      }
      printf(" ");
      second = 0;
      first++;
    }
    return 0;
  }