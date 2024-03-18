/* name: Ofir Haruvi */
/* ID: 313362006 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "set.h"

/* the program is a set calculator - */
/* it can add elements to a set, print it, and operate binary operation between two sets: */
/* union, intersect, subtract, and symmetrical difference. */
/* the user enters a string with a command to to activate a calculation.*/
/* in order to stop the program, the user should enter "stop" */
int main() {
    int i;
    char str[MAX_STR_SIZE]; /* the input string */
    char strCopy[MAX_STR_SIZE]; /* a copy of the input string */
    char bO; /* char indicator of a binary operation */
    char *binOp; /* pointer to the binary operation in the string */

    set sets[NUM_OF_SETS]; /* a set of sets: */
    /* 0-SETA, 1-SETB, 2-SETC, 3-SETD, 4-SETE, 5-SETF */

    for (i = 0; i < 6; i++) /*reset the all the sets */
    {
        resetSet(&sets[i]);
    }

    start(); /* a friendly message for the beginning of the program */

    printf("Enter a binary operation and set\\s: \n");
    if (fgets(str, MAX_STR_SIZE, stdin) == NULL) /* get the input string. if EOF - terminate program */
    {
        printf("error: EOF, but no stop command was given.\n"); /* EOF */
        exit(1);
    }
    removeEnter(str); /* remove the following enter (if there is) in the string */
    strcpy(strCopy, str); /* copy the string */
    printf("\nthe string is: %s\n", str);
    while (strcmp(str, "stop")) { /* while the command stop didn't enter */
        if (isDoubleComa(str)) { /* if there is double comma */
            printf("Multiple consecutive commas\n\n"); /* error */
            goto next; /* go get the next input string */
        }
        if (isIllegalComa(str)) { /* if there is illegal coma */
            printf("Illegal comma\n\n"); /* error */
            goto next; /* go get the next input string */
        }
        if (isSpaceWithoutComma(str)) { /* if there is illegal space without coma */
            printf("Missing comma\n\n"); /* error */
            goto next; /* go get the next input string */
        }

        binOp = strtok(str, SPACE_DEL); /* find out which binary operation */

        if (!binOp) { /* if there is no binary operation name at all */
            printf("Empty String\n\n"); /* error */
            goto next; /* go get the next input string */
        }
        bO = binaryOp(binOp); /* char indicator of the group */
        if (isCommaAtTheEnd(strCopy)) { /* if there is an illegal comma at the end of the string */
            printf("Extraneous text after end of command\n\n"); /* error */
            goto next; /* go get the next input string */
        }
        correctInput(bO, sets); /* doing the command in the string */
        next:; /* the end of operation on a given string*/

        printf("Enter a binary operation and set\\s: \n");
       if (fgets(str, MAX_STR_SIZE, stdin) == NULL) /* get the input string. if EOF - terminate program */
        {
            printf("error: EOF, but no stop command was given.\n"); /* EOF */
            exit(1);
        }
        removeEnter(str); /* remove tailing enter */
        strcpy(strCopy, str); /* copy the string */
        printf("\nthe string is: %s\n", str);
        /* starting all over again */
    }

    stop(); /* a friendly message for the ending of the program */

    return 0;
}

