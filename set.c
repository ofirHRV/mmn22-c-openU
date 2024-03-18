#include <stdio.h>
#include "set.h"

/* resetSet: reset a set */
void resetSet(set* inputSet)
{
    int i;

    for (i = 0; i < NUM_OF_CHARS_128_BIT; i++)
    {
        inputSet->values[i] = 0;
    }
}

/* read_set: add value to set */
void read_set(set* set, int value)
{
    set_bit_in_byte(&set->values[value / BIT_IN_BYTE], value % BIT_IN_BYTE);
}

/* print_set: print set */
void print_set(set* set) {
    int i, j;

    int count = 0;  /* keeps track of number elements in a row */

    for (i = 0; i < NUM_OF_CHARS_128_BIT; i++) {
        for (j = 0; j < BIT_IN_BYTE; j++) {
            if (test_bit_in_byte(set->values[i], j)) {
                count++;
                if (count < NUM_ELEMENT_ROW)
                    printf("%-3d ", (i * BIT_IN_BYTE + j));
                else {   /* the sixteenth element */
                    count = 0;
                    printf("%-3d\n", (i * BIT_IN_BYTE + j));
                }
            }
        }
    }
    if (count == 0) /* if there's no elements in the set */
        printf("The set is empty");
    printf("\n");
    printf("print_set -V-\n");
}


/* union_set: unite set1 elements with set2 elements and put the result in set3 */
void union_set(set* set1, set* set2, set* set3) {
    int i, j;
    set temp; /* temporary set */
    resetSet(&temp); /* reset temporary set */
    
    for (i = 0; i < NUM_OF_CHARS_128_BIT; i++) { /* the chars - bytes */
        for (j = 0; j < BIT_IN_BYTE; j++) { /*the bits in byte*/
            if (test_bit_in_byte(set1->values[i], j) || test_bit_in_byte(set2->values[i], j))
                /* if the element exist in set1 or set 2 */
                set_bit_in_byte(&temp.values[i], j); /* add it to temp */
        }
    }
    copySet(&temp, set3); /* copy the result to set3 */
    printf("union_set -V-\n");
}

/* intersect_set: intersect set1 elements with set2 elements and put the result in set3 */
void intersect_set(set* set1, set* set2, set* set3)
{
    int i, j;
    set temp; /* temporary set */
    resetSet(&temp); /* reset temporary set */  

    for (i = 0; i < NUM_OF_CHARS_128_BIT; i++) { /* the chars - bytes */
        for (j = 0; j < BIT_IN_BYTE; j++) { /*the bits in byte*/
            if (test_bit_in_byte(set1->values[i], j) && test_bit_in_byte(set2->values[i], j))
                /* if the element exist in set1 and set 2 */
                set_bit_in_byte(&temp.values[i], j); /* add it to temp */
        }
    }
    copySet(&temp, set3); /* copy the result to set3 */
    printf("intersect_set -V-\n");
}

/* sub_set: subtract set2 elements from set1 elements and put the result in set3 */
void sub_set(set* set1, set* set2, set* set3) {
    int i, j;
    set temp; /* temporary set */
    resetSet(&temp); /* reset temporary set */

    for (i = 0; i < NUM_OF_CHARS_128_BIT; i++) { /* the chars - bytes */
        for (j = 0; j < BIT_IN_BYTE; j++) {  /*the bits in byte*/
            if (test_bit_in_byte(set1->values[i], j) && test_bit_in_byte(set2->values[i], j))
                /* if the element exist in set1 and set 2 */
                continue; /* ignore it */
            else if (test_bit_in_byte(set1->values[i], j))
                /* if the element exist in set1 and not in set 2 */
                    set_bit_in_byte(&temp.values[i], j); /* add it to temp */
        }
    }
    copySet(&temp, set3); /* copy the result to set3 */
    printf("sub_set -V-\n");
}


/* symdiff_set: compute symmetric difference of set1 elements and set2 elements and put the result in set3 */
void symdiff_set(set* set1, set* set2, set* set3) {
    int i, j;
    set temp;  /* temporary set */
    resetSet(&temp); /* reset temporary set */    

    for (i = 0; i < NUM_OF_CHARS_128_BIT; i++) { /* the chars - bytes */
        for (j = 0; j < BIT_IN_BYTE; j++) { /*the bits in byte*/
            if (test_bit_in_byte(set1->values[i], j) && test_bit_in_byte(set2->values[i], j))
                /* if the element exist in set1 and set 2 */
                continue; /* ignore it */
            else if (test_bit_in_byte(set1->values[i], j))
                /* if the element exist in set1 and not in set2 */
                set_bit_in_byte(&temp.values[i], j); /* add it to temp */
            else if (test_bit_in_byte(set2->values[i], j))
                /* if the element exist in set2 and not in set1 */
                set_bit_in_byte(&temp.values[i], j); /* add it to temp */
        }
    }
    copySet(&temp, set3); /* copy the result to set3 */
    printf("symdiff_set -V-\n");
}

/* copySet: copy set copyFrom to set copyTo */
void copySet(set* copyFrom, set* copyTo)
{
    int i, j;
    for (i = 0; i < NUM_OF_CHARS_128_BIT; i++) { /* the chars - bytes */
        for (j = 0; j < BIT_IN_BYTE; j++) {  /*the bits in byte*/
            if (test_bit_in_byte(copyFrom->values[i], j)) /* if a bit is on in copyFrom */
                set_bit_in_byte(&copyTo->values[i], j); /* turn it on in copyTo */
            else /* if a bit is off in copyFrom */
                clear_bit_in_byte(&copyTo->values[i], j); /* turn it off in copyTo */
        }
    }
}

/* test_bit_in_byte: test if a bit is on or off. if on - return 1. if off - return 0. */
int test_bit_in_byte(unsigned char byte, int bitIndex) {

    if (byte & (1 << bitIndex)) {
        return 1;
    } else {
        return 0;
    }
}

/* set_bit_in_byte: turn on a bit */
void set_bit_in_byte(unsigned char *pByte, int bitIndex)
{
    (*pByte) |= (1 << bitIndex);
}

/* clear_bit_in_byte: turn off a bit */
void clear_bit_in_byte(unsigned char *pByte, int bitIndex) {
    (*pByte) &= ~(1 << bitIndex);
}





