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

#ifndef MYFREETICKETS
TODO(USING THE SOLUTION freetickets.c NOT MY CODE)
#else

/*
 * freetickets
 *      tears down the database freeing all allocated memory
 *      count the number of tickets freed in the database and
 *      print it out before returning
 *
 *      unsigned long cnt = 0UL
 *      printf("Total tickets freed: %lu\n", cnt);
 */
void
freetickets(void)
{
    int empty = 1; // set to zero when there is at least one vehicle in the database

    /*
     * walk down each chain
     */
     uint32_t index = 0;            // index to transverse through htable
     long unsigned int cnt = 0;     // count tickets that were freed
     struct vehicle *currvehicle;   // pointer to current vehicle node
     struct vehicle *savedvehicle;  // pointer to saved vehicle node
     struct ticket *currticket;     // pointer to current ticket node
     struct ticket *savedticket;    // pointer to saved vehicle node
     for (index = 0U; index < tabsz; index++) {
	 // update the htable value
         currvehicle = *(htable + index);
	 while (currvehicle != NULL) {
	     empty = 0;
	     currticket = currvehicle->head;
	     while (currticket != NULL) {
		 // remove all the tickets for all vehicles on chain
	         savedticket = currticket;
		 currticket = currticket->next;
		 free(savedticket);
		 cnt++;
	     }
	     // free the vehicle
	     free(currticket);
	     savedvehicle = currvehicle;
	     // assign pointer to next vehicle node
	     currvehicle = currvehicle->next;
	     free(savedvehicle->state);
	     free(savedvehicle->plate);
	     free(savedvehicle);
	 }
	 // chain is removed
	 free(currvehicle);
	 *(htable+index) = NULL;
     }

    if (empty)
        printf("Empty Database\n");
    printf("Total tickets freed: %lu\n", cnt);
    return;
}
#endif
