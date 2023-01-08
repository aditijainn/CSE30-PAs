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

#ifndef MYSUMLOOKUP
TODO(USING THE SOLUTION sumlookup.c NOT MY CODE)
#else

/*
 * summlookup
 *     find the vehicle with a specified summons number
 * Input:
 *      summ: string of summons number
 * returns:   a pointer to the vehicle
 */
struct vehicle *
sumlookup(char *summ)
{
    unsigned long long summid;

    if (strtosumid(summ, &summid) != 0) {
        fprintf(stderr, "%s:sumlookup bad summons number:%s\n", argv0, summ);
        return NULL;
    }
    
    uint32_t index = 0;      // updates to transverse through htable
    struct vehicle *chain;   // pointer to vehicle struct node
    struct ticket *ptr;      // pointer to ticket struct node
    for (index = 0U; index < tabsz; index++) {
        chain = *(htable + index);
	// transerve through vehicle nodes
	while (chain != NULL) {
	    ptr = chain->head;
	    while (ptr != NULL) {
		// if summons is found
	        if (ptr->summons == summid) {
	            return chain;
                } else {
		    ptr  = ptr->next;
	        }
	    }
	    // update to next vehicle struct node
	    chain = chain->next;
	}
    }
    return NULL;
}
#endif
