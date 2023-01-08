#include <stdio.h>
#include "wrtrow.h"

/*
 * wrtrow
 *
 * usage:   given an array of pointers to columns and an array of columns to
 *          ouput and a count of output columns
 *          output those columns specified in the output array (contents are
 *          index numbers of the input array)
 * args:
 *  ptable  points at array of pointers each element points at a data field
 *  coltab  points array of ints each element is an index in ptable in print order
 *  outcols number of elements in array coltab
 *  outdelim the output field delimiter to use
 */
void
wrtrow(char **ptable, int *coltab, int outcols, char outdelim)
{
     int i = 0;
     int cols = 0;
     for(int x = 0; x<outcols; x++) {         // loops until all outcols are done
	 int val = *(coltab+i)-1;             // sets index offset for ptable
	 if(cols == outcols-1) {
	     printf("%s\n", (*(ptable+val)));
	 } else {
             printf("%s%c",(*(ptable+val)), outdelim);
	 }
	 i++;
	 cols++;
     }
}
