#include <stdio.h> 
#include <string.h>
  int main(int argc, char * argv[]) {

  /* assuming there is only one argument or string, I store it using a char array */
  int i = 0;

  int count = 0;

  int complength = 0;

  char check = argv[1][i];

  int x = 0;

  char compArray[strlen(argv[1])];

  /* check if there are any digits and print out error if there are any*/
  while (argv[1][x] != 0) {

    if (argv[1][x] >= 48 && argv[1][x] <= 57) {

      printf("%s", "error");

      return -1;

    }

    x++;

  }

  while (argv[1][i] != 0) {

    char c = argv[1][i];

    /* need to check if it's a new character, */
    /* check to see if it's char from a-z, A-Z, or punctuation */
    if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90) || (c == 33) || (c == 44) || (c == 46) || (c == 63)) {

      if (c == check) {

        count++;

        if (count == 1) {

          compArray[complength] = c;

          complength++;

        }

      } else {

        /* what this does is ensure that the compression number is stored, in the form of a one digit number */
        if (count < 10) {

          compArray[complength] = count + '0';

        }

        /* what this does is ensure that the compression number is stored, in the form of a two digit number */
        else if (count >= 10) {

          compArray[complength] = (count / 10) + '0';

          complength++;

          compArray[complength] = (count - (count / 10) * 10) + '0';

        }

        complength++;

        count = 1;

        if (count == 1) {

          compArray[complength] = c;

          complength++;

        }

      }

    }

    i++;

    check = argv[1][i - 1];

  }

  if (count < 10) {

    /* same as above, in that it stores one-digit or two-digit number */
    compArray[complength] = count + '0';

  } else if (count >= 10) {

    printf("%d", count);

    compArray[complength] = (count / 10) + '0';

    complength++;

    compArray[complength] = (count - (count / 10) * 10) + '0';

  }

  complength++;

  /* if the compression length is longer than the original string, print out the original string*/
  if (complength > i) {

    printf("%s", argv[1]);

  } else {

    /* if compression length is shorter than the original string, print out the compression string*/
    int a = 0;

    for (a = 0; a < complength; a++) {

      printf("%c", compArray[a]);

    }

  }

  return 0;

}
