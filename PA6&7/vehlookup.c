#include <limits.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "parking.h"
#include "hashdb.h"

#ifndef MYVEHLOOKUP
TODO(USING THE SOLUTION vehlookup.c NOT MY CODE)
#else

/*
 * vehiclelookup
 *          look for vehicle in the database
 *          vehicle must match both plate and state strings
 * args
 *  plate   plate id string to be found
 *  state   state id string to be found
 *
 * returns  pointer to vehicle if found NULL otherwise
 */

struct vehicle *
vehiclelookup(char *plate, char *state)
{
    // (void)plate;    // delete this when you write your code
    // (void)state;    // delete this when you write your code
    // return NULL; // delete this when you write your code

    uint32_t hashval;              // hashvalue to insert into hashtable
    struct vehicle *ptr;           // pointer to struct vehicle ptr
    hashval = hash(plate) % tabsz; 
    ptr = *(htable + hashval);

    while (ptr != NULL) {
        if ((strcmp(plate, ptr->plate) == 0) && 
	(strcmp(state, ptr->state) == 0)) {  // check license plate
	    break;
	} else {
	    ptr = ptr -> next; // assign pointer to next
	}
    }  
    return ptr;
}
#endif
