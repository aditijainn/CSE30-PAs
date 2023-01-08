#include <limits.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "parking.h"

#ifndef MYLARGEST
TODO(USING THE SOLUTION largest.c NOT MY CODE)
#else

/*
 * largest
 *     find the vehicle with the largest number of
 *     tickets and largest fine in database
 *     and print it
 */
void
largest(void)
{
    struct vehicle *count = NULL; // vehicle with largest number of tickets
    struct vehicle *fine = NULL;  // vehicle with largest total fine

/* your code here */
    uint32_t index = 0;           // index to update chain ptr value
    uint32_t largestfine = 0;     // largest fine value
    uint32_t greatesttickets = 0; // greatest tickets value
    struct vehicle *chain;        // pointer to vehicle struct
    for (index = 0U; index < tabsz; index++) {
        chain = *(htable + index);
	// transverse through vehicles struct nodes
	while (chain != NULL) {
	    // update variables if found a larger fine
	    if (chain->tot_fine >= largestfine) {
                fine = chain;
		largestfine = fine->tot_fine;
	    }
	    // update variables if found greater ticketa
	    if (chain->cnt_ticket >= greatesttickets) {
		count = chain;
		greatesttickets = count->cnt_ticket;
	    }
	    // point to next chain
	    chain = chain->next;
	}
    }


    if ((count == NULL) || (fine == NULL)) {
        printf("Empty database\n");
        return;
    }
    printf("Most tickets Plate: %s, State: %s tickets: %u, total fine: $%u\n",
            count->plate, count->state, count->cnt_ticket, count->tot_fine);
    printf("Largest fine Plate: %s, State: %s tickets: %u, total fine: $%u\n",
            fine->plate, fine->state, fine->cnt_ticket, fine->tot_fine);
    return;
}
#endif
