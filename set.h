#ifndef SET
#define SET

#define NUM_ELEMENT_ROW  16 /* number of elements in a row */
#define NUM_OF_CHARS_128_BIT 16 /* the num of chars which contain 128 bits */
#define BIT_IN_BYTE 8 /*number of bits in byte */
#define MAX_STR_SIZE 1024 /* maximum string size */
#define SPACE_DEL " \t" /* space delimiter */
#define COMA_SPACE_DEL ", \t" /* comma and space delimiter */
#define NUM_OF_SETS 6 /* number of sets */
#define MAX_ELEMENTS 128 /* maximum number of elements from 0-127*/

typedef struct set {
    unsigned char values[NUM_OF_CHARS_128_BIT];
} set; /* a set */

/* ********************************************************************** */
/* *************************functions of set.c: ************************* */
/* ********************************************************************** */

void resetSet(set* inputSet);
/* resetSet: reset a set */

void read_set(set* set, int value);
/* read_set: add value to set */

void print_set(set* set);
/* print_set: print a set */

void union_set(set* set1, set* set2, set* set3);
/* union_set: unite set1 elements with set2 elements and put the result in set3 */

void intersect_set(set* set1, set* set2, set* set3);
/* intersect_set: intersect set1 elements with set2 elements and put the result in set3 */

void sub_set(set* set1, set* set2, set* set3);
/* sub_set: subtract set2 elements from set1 elements and put the result in set3 */

void symdiff_set(set* set1, set* set2, set* set3);
/* symdiff_set: Compute symmetric difference of set1 elements and set2 elements and put the result in set3 */

void copySet(set* copyFrom, set* copyTo);
/* copySet: copy set copyFrom to set copyTo */

int test_bit_in_byte(unsigned char byte, int bitIndex);
/* test_bit_in_byte: test if a bit is on or off. if on - return 1. if off - return 0. */

void set_bit_in_byte(unsigned char *pByte, int bitIndex);
/* set_bit_in_byte: turn on a bit */

void clear_bit_in_byte(unsigned char *pByte, int bitIndex);
/* clear_bit_in_byte: turn off a bit */



/* ********************************************************************** */
/* ************************ functions of input.c: *********************** */
/* ********************************************************************** */


void start(void);
/* start: a friendly message for the beginning of the program */

void stop(void);
/* stop: a friendly message for the ending of the program */

char binaryOp(char* binOp);
/* binaryOp: check which binary operation is chosen and return: */
/* 'r' for read_set;  'p' for print_set; 'u' for union_set; */
/* 'i' for intersect_set;  's' for sub_set; 'y' for symdiff_set */
/*  and 'x' for undefined command */

void correctInput(char bO, set sets[]);
/* correctInput: identifies the user's desired action and performs it */
/* (bO = binary operation) */

int whichGroup(char* group);
/* whichGroup: identifies which group was passed in the input string and returns its index in the sets array */
/* if group doesn't exist: return -1 */

char isNumber(char *text);
/* isNumber: check if a string in a number. if so return 1, else return 0 */

void removeEnter(char s[]);
/* removeEnter: remove '\n' from the end of a string.
deals with situation where the function fgets can end an input with '\n', but the '\n' counted as a character. */

int validGroupNum (int num);
/* validGroupNum: check if the given number is an index in sets - a valid set */
/* if so return 1. else return 0*/

int isGroup(char* maybeGroup);
/* isGroup: check is set name in the string is empty. return 0 if it's empty and 1 if not */

void validReadSet (char* member, int fGroup, set sets[]);
/* validReadSet: read members to a given set (fGroup) in sets */
/* if the member adding operation didn't terminate correctly (with -1 at the end) - prints an error and */
/* not adding the members to the group */

int isDoubleComa(char str[]);
/* isDoubleComa: check if there is mote than two commas in a row in the string input */
/* if there is: return 1, else: return 0*/

int isSpaceWithoutComma (char str[]);
/* isSpaceWithoutComma: check if there is no comma between arguments where it shouldn't be */
/* (- between groups and members in the input)  if there is - return 1. else: return 0 */

int isIllegalComa(char str[]);
/*isIllegalComa: check is there is comma where it shouldn't be  */
/* ( - between the binary operation and the first group */
/* if there is: return 1. else: return 0*/

int isCommaAtTheEnd(char str[]);
/*isCommaAtTheEnd: check is there is comma in the end of the input */
/* if there is: return 1. else: return 0 */



#endif

