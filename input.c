#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "set.h"

/* start: a friendly message for the beginning of the program */
void start()
{
    printf("\n");
    printf("******************************************************************************************************************\n");
    printf("************************************** Hello, and welcome to the SET CALCULATOR! *********************************\n");
    printf("******************************************************************************************************************\n");
    printf("\n");
    printf("                        Just choose a binary operation, a set or sets, and get started! YAY!                      \n");
    printf("\n");
}

/* stop: a friendly message for the ending of the program */
void stop()
{
    printf("\n");
    printf("******************************************************************************************************************\n");
    printf("\n");
    printf("                                   Thank you for using the SET CALCULATOR!                                        \n");
    printf("                                                       BYE-BYE!                                                    \n");

    exit(0);

}
/* binaryOp: check which binary operation is chosen and return: */
/* 'r' for read_set;  'p' for print_set; 'u' for union_set; */
/* 'i' for intersect_set;  's' for sub_set; 'y' for symdiff_set */
/*  and 'x' for undefined command */
char binaryOp(char* binOp)
{
    if (!strcmp(binOp, "read_set"))
        return 'r';
    else if (!strcmp(binOp, "print_set"))
        return 'p';
    else if (!strcmp(binOp, "union_set"))
        return 'u';
    else if (!strcmp(binOp, "intersect_set"))
        return 'i';
    else if  (!strcmp(binOp, "sub_set"))
        return 's';
    else if (!strcmp(binOp, "symdiff_set"))
        return 'y';
    else { /* if undefined command */
        printf("Undefined command name\n\n"); /* error */
        return 'x';
    }
}
 /* correctInput: identifies the user's desired action and performs it */
 /* (bO = binary operation) */
void correctInput(char bO, set sets[])
{
    int fGroup, sGroup, tGroup ; /* the index of the first group, second group, third group */
	char* group1, *group2, *group3, *group4; /* pointer to the first group, second group, third group, and the porth test group */
	char* member; /* a pointer to the first member of the group */

    if (bO == 'r') { /* if the wanted operation is to read to a set */
        printf("read_set func activated~\n");
        group1 = strtok(NULL, COMA_SPACE_DEL); /*find out for which set */
        if (!isGroup(group1)) { /* if there is no set name at all */
            printf("Missing parameter\n\n"); /* error */
            goto next; /* go to the end of the func*/
        }
        fGroup = whichGroup(group1); /* set fgroup as the index of the of chosen set in sets */
        if (!validGroupNum(fGroup)) { /* if not a valid group */
            printf("Undefined set name\n\n"); /* error */
            goto next; /* go to the end of the func */
        }
        member = strtok(NULL, COMA_SPACE_DEL); /* check for the first member to add to the set */
        if (!member) { /* if no member exist */
            printf("List of set members is not terminated correctly\n\n"); /* error (because the member stream needs to end with -1 in any case) */
            goto next; /* go to the end of the func */
        }
        sGroup = whichGroup(member); /* check if there is an extra set name given in the input string */
        if (validGroupNum(sGroup)) { /* check if valid set */
            printf("Extraneous text after end of command\n\n"); /* error. there should be only one set in this command */
            goto next; /* go to the end of the func */
        }
        validReadSet(member, fGroup, sets); /* read the members to the given set */
        printf("\n");
        }
    else if (bO == 'p') /* if the wanted operation is to print a set */
    {
        printf("print_set func activated~\n");
        group1 = strtok(NULL, COMA_SPACE_DEL); /* find out for which set */
        printf("The set is: %s \n", group1);
        if(!isGroup(group1)) { /* if there is no set name at all */
            printf("Missing parameter\n\n"); /* error */
            goto next; /* go to the end of the func */
        }
        fGroup = whichGroup(group1); /* set fgroup as the index of the of chosen set in sets */
        group2 = strtok(NULL, COMA_SPACE_DEL); /* check if there is more input after the given group */
        if (group2 != NULL) { /* if there is */
            printf("Extraneous text after end of command\n\n"); /* error */
            goto next; /* go to the end of the func */
        }
       if (!validGroupNum(fGroup)) { /* if not a valid group */
           printf("Undefined set name\n\n"); /* error */
           goto next; /* go to the end of the func */
       }
       print_set(&sets[fGroup]); /* print the chosen set */
       printf("\n");
    }
    else if (bO == 'u' || bO == 'i' || bO == 's' || bO == 'y')
        /* if the wanted operation is union, intersect, subtraction or symmetric difference */
    {
        if (bO == 'u')
            printf("union_set func activated~\n");
        else if (bO == 'i')
            printf("intersect_set func activated~\n");
        else if (bO == 's')
            printf("sub_set func activated~\n");
        else
            printf("symdiff func activated~\n");

        group1 = strtok(NULL, COMA_SPACE_DEL);  /* find out the first set */
        if(!isGroup(group1)) { /* if there is no set name at all */
            printf("Missing parameter\n\n"); /* error */
            goto next; /* go to the end of the func */
        }
        fGroup = whichGroup(group1); /* set fgroup as the index of the of chosen set in sets */
        group2 = strtok(NULL, COMA_SPACE_DEL);  /* find out the second set */
        if(!isGroup(group2)) { /* if there is no set name at all */
            printf("Missing parameter\n\n"); /* error */
            goto next; /* go to the end of the func */
        }
        sGroup = whichGroup(group2); /* set fgroup as the index of the of chosen set in sets */
        group3 = strtok(NULL, COMA_SPACE_DEL);  /* find out the third set */
        if(!isGroup(group3)) { /* if there is no set name at all */
            printf("Missing parameter\n\n"); /* error */
            goto next; /* go to the end of the func */
        }
        tGroup = whichGroup(group3); /* set fgroup as the index of the of chosen set in sets */
        group4 = strtok(NULL, COMA_SPACE_DEL); /* check if there is more input after the last group */
        if (group4 != NULL) { /* if there is */
            printf("Extraneous text after end of command\n\n"); /* error */
            goto next; /* go to the end of the func */
        }
        if (!validGroupNum(fGroup) || !validGroupNum(sGroup) || !validGroupNum(tGroup)) {
            /* check if there are invalid sets */
            printf("Undefined set name\n\n"); /* error */
            goto next;  /* go to the end of the func */
        }

        if (bO == 'u') /* if the operation is union */
            union_set(&sets[fGroup], &sets[sGroup], &sets[tGroup]); /* union sets */
        else if (bO == 'i') /* if the operation is intersect */
            intersect_set(&sets[fGroup], &sets[sGroup], &sets[tGroup]); /* intersect sets */
        else if (bO == 's') /* if the operation is  subtraction */
            sub_set(&sets[fGroup], &sets[sGroup], &sets[tGroup]); /*  subtraction sets */
        else /* if the operation is symmetric difference */
            symdiff_set(&sets[fGroup], &sets[sGroup], &sets[tGroup]); /* symmetric differenc sets */
        printf("\n");
    }
    next:; /* the end of the function */

}

/* whichGroup: identifies which group was passed in the input string and returns its index in the sets array */
/* if group doesn't exist: return -1 */
int whichGroup(char* group) {
    if (!strcmp(group, "SETA"))
        return 0;
    else if (!strcmp(group, "SETB"))
        return 1;
    else if (!strcmp(group, "SETC"))
        return 2;
    else if (!strcmp(group, "SETD"))
        return 3;
    else if (!strcmp(group, "SETE"))
        return 4;
    else if (!strcmp(group, "SETF"))
        return 5;
    else {
        return -1;
    }
}

/* isNumber: check if a string in a number. if so return 1, else return 0 */
char isNumber(char *text)
{
    int j;
    j = strlen(text);
    while(j--)
    {
        if(text[j] >= '0' && text[j] <= '9')
            continue;

        return 0;
    }
    return 1;
}

/* removeEnter: remove '\n' from the end of a string.
deals with situation where the function fgets can end an input with '\n', but the '\n' counted as a character. */
void removeEnter(char s[])
{
    if (strlen(s) >= 1) /* if there is a chance that the string contains an '\n' */
        if (s[strlen(s)-1] == '\n')
            s[strlen(s)-1] = '\0';
}

/* validGroupNum: check if the given number is an index in sets - a valid set */
/* if so return 1. else return 0*/
int validGroupNum (int num)
{
    if (num >=0 && num < NUM_OF_SETS)
        return 1;
    return 0;
}

/* isGroup: check is set name in the string is empty. return 0 if it's empty and 1 if not */
int isGroup(char* maybeGroup)
{
    if (!maybeGroup) /* if the set name is empty */
        return 0;
    return 1; /* if the set name isn't empty */
}



/* validReadSet: read members to a given set (fGroup) in sets */
/* if the member adding operation didn't terminate correctly (with -1 at the end) - prints an error and */
/* not adding the members to the group */
void validReadSet (char* member, int fGroup, set sets[])
{
    set temp; /* temporary set */
    int flagMinusOne = 0; /* flag to indicate if there is a -1 at the end ot the input */
    resetSet(&temp);
    while (member != NULL) { /* if there is a next member */
        if (atoi(member) >= MAX_ELEMENTS || atoi(member) <= -2) { /* if the member isn't in range */
            printf("Invalid set member - value out of range\n"); /* error */
            return; /* end the function :( */
        }
        if (!isNumber(member) && atoi(member)!= -1) { /* if the member is not a number */
            printf("Invalid set member - not an integer\n"); /* error */
            return; /* end the function :( */
        }
        
        if (flagMinusOne == 1) { /* if -1 is already entered, but there is more input in the string */
            printf("List of set members is not terminated correctly\n"); /* error */
            return;/* end the function :( */
        }
        if (atoi(member) == -1) /* if the given member is -1 */
        {
            flagMinusOne = 1;
        }

        read_set(&temp, atoi(member)); /* read member to temp */
        member = strtok(NULL, COMA_SPACE_DEL); /* move to the next member */
    }
    if (flagMinusOne) { /* if there was -1 at the end of the member stream */
        resetSet(&sets[fGroup]); /* reset the given set */
        copySet(&temp, &sets[fGroup]); /* copy temp to the given set */
        printf("read_set -V-\n");
        return;
    }
    else { /* if there wasn't a -1 at the end of the member stream */
        printf("List of set members is not terminated correctly\n"); /* error */
        return; /* end the function :( */
    }
}

/* isSpaceWithoutComma: check if there is no comma between arguments where it shouldn't be */
/* (- between groups and members in the input)  if there is - return 1. else: return 0*/
int isSpaceWithoutComma (char str[])
{
    int space = 0; /* space flag */
    int notSpace = 0; /* character other than space flag */
    int i = 0;
    for (; i < strlen(str); i++) { /* skip legal space without comma after the binary operation */
        if (str[i] != '\t' && str[i] != ' ') { /* if there is notSpace */
            if (space == 0)
                notSpace = 1; /* there is a space */
            else { /* if we reached the end of the legal space and arguments place*/
                space = 0; /* reset space */
                notSpace = 0; /* reset no space */
                break;
            }
        }
        else if ((str[i] == '\t' || str[i] == ' ') && notSpace == 1) /* if there is space */
            space = 1; /* there is space */
    }

    for (; i < strlen(str); i++) { /* looking for spaces without comma */
        if (str[i] != '\t' && str[i] != ' ' && str[i] != ',') { /* if there is notSpace */
            if (space == 0) /*is there wasn't a space before */
                notSpace = 1; /* there is a notSpace */
            else /* there is a space without comma */
                return 1;
        }
        else if ((str[i] == '\t' || str[i] == ' ') && notSpace == 1) /* if there is a space */
            space = 1; /* there is a space */
        else if (str[i] == ',') { /* if there is a comma */
            notSpace = 0; /* reset notSpace */
            space = 0; /* reset space */
        }
    }
    return 0; /* there isn't a space without comma */
}

/*isIllegalComa: check is there is comma where it shouldn't be  */
/* ( - between the binary operation and the first group */
/* if there is: return 1. else: return 0*/
int isIllegalComa(char str[])
{
    int notSpace = 0; /* character other than space flag */
    int passCommand = 0; /* we passed the binary operation flag */
    int i;
    for (i = 0; i < strlen(str); i++) { /* skip legal space without comma after the binary operation */
        if (str[i] != '\t' && str[i] != ' ' && str[i] != ',') { /* if there not space or comma */
            if (passCommand > 0) /* if we already passed the binary operation */
                return 0; /* no illegal comma */
            notSpace = 1; /* there is notSpace */
        }
        else if (notSpace == 1) { /* if there is notSpace*/
            if (str[i] == ',') /* if we found a comma */
                return 1; /* there is an illegal coma */
            passCommand = 1; /* we passed the binary operation */
        }
    }
    return 0; /* no illegal comma */
}
/*isCommaAtTheEnd: check is there is comma in the end of the input */
/* if there is: return 1. else: return 0*/
int isCommaAtTheEnd(char str[])
{
    int i;
    for (i = strlen(str)-1; i>=0; i--) { /* going through on the input string from end to start */
        if (str[i] != ' ' && str[i] != '\t' && str[i] != ',') /* if we reached to the text without encounter commas */
            return 0; /* there is no comma at the end */
        if (str[i] == ',') /* if we encounter comma */
            return 1; /* there is comma at the end */
    }
    return 0; /* there is no comma at the end */
}

/* isDoubleComa: check if there is mote than two commas in a row in the string input */
/* if there is: return 1, else: return 0*/
int isDoubleComa(char str[])
{
    int i;
    int count; /* count the number of commas in a row */
    for (i = 0; i < strlen(str); i++) {

        if (str[i] == ',') /* if we found comma */
            count++;
        else if (str[i] != ',' && str[i] != ' ' && str[i] != 't') /* if there is no comma in a row */
            count = 0; /* reset count */
        if (count >= 2) /* if there is two commas in a row */
            return 1; /* there is double comma */
    }
    return 0; /* there is no double comma */
}




