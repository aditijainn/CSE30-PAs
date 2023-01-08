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

#ifndef MYDELTICKET
TODO(USING THE SOLUTION delticket.c NOT MY CODE)
#else

/*
 * delticket
 *      remove ticket (summons) from the database
 *      look up the summons for a vehicle and pay it (remove the ticket) 
 *
 *      Find the vehicle by the state and plate. if not found return -1
 *
 *      convert the summ string to a long long int using
 *      using strtosumid. This long long int is how the summons number
 *      is stored in the database in struct ticket.
 *      After being converted you can use it find a summons id match
 *      in the linked list of tickets attached to the strcut vehicle.      
 *
 *      After you have the vehicle, find the summons on the ticket chain
 *      that matches the converted summons string (summid in the example)
 *      example:
 *        unsigned long long summid
 *        if (strtosumid(summ, &summid) != 0)
 *           return -1;
 *        now search the ticket chain to find that summons
 *        struct ticket *tptr;
 *        if (tptr->summons == summid)
 *          found it
 *           
 *      If found, delete it from the ticket chain. If the vehicle
 *      no longer has any tickets, then remove the vehicle from the hash chain
 *      Otherwise you must update the tot_fine and cnt_tickets fields in
 *      the struct vehicle so the are accurate after removing the summons
 *      Make sure to delete all space that malloc()'d 
 *
 * Inputs:
 *  plate   plate id string to be found
 *  state   state id string to be found
 *  summ    summon id string to be found
 *
 * returns 0 if ok -1 if not found or error
 */

int
delticket(char *plate, char *state, char *summ)
{
    unsigned long long summid;     // converting summ to long
    struct ticket *ticketptr;      // ptr to curr ticket
    struct ticket *prevticket;     // ptr to previous ticket
    struct vehicle *vehlookupptr;  // ptr to vehicle looked up
    struct vehicle *prevveh = NULL; // ptr to previous vehicle 
    uint32_t hashval;              // hashvalue to insert into hashtable        
    hashval = hash(plate) % tabsz;
    vehlookupptr = *(htable + hashval);

    while (vehlookupptr != NULL) {
        if ((strcmp(plate, vehlookupptr->plate) == 0) &&
	(strcmp(state, vehlookupptr->state) == 0)) {  // check license plate
	    break;
	} else {
	    prevveh = vehlookupptr;
	    vehlookupptr = vehlookupptr->next; // assign pointer to next
	}
    }

    /*
     * convert the summons string to a number
     */
    if (strtosumid(summ, &summid) != 0)
        return -1;

    /*
     * first find the vehicle
     */
    if (vehlookupptr == NULL) {                   // case for vehicle not found
        return -1;
    } else {                                      // case for vehicle found
	ticketptr = vehlookupptr->head;
	while (ticketptr->next != NULL) {         // loop through tickets
	    if (ticketptr->summons == summid) {
	         break;
	    } else {
		 prevticket = ticketptr;          // set previous ticket
		 ticketptr = ticketptr->next;
	    }
	}
	if (ticketptr->summons != summid) {       // case for last ticket
	    return -1;
	} 
	if (ticketptr == vehlookupptr->head) {    // case for first ticket
	    vehlookupptr->head = ticketptr->next;
	} else {
	    prevticket->next = ticketptr->next;
	}
	vehlookupptr->tot_fine -= fineTab[ticketptr->code].fine;
	vehlookupptr->cnt_ticket -= 1;

        // case for only ticket deleted
	if (vehlookupptr->cnt_ticket == 0 && vehlookupptr->tot_fine == 0) { 
	    if (prevveh == NULL) {
		*(htable + hashval) = vehlookupptr->next;
	    } else {
		prevveh->next = vehlookupptr->next;
	    }
	free(vehlookupptr->plate);
	free(vehlookupptr->state);
	free(vehlookupptr);
	}
    }
    free(ticketptr);
    return 0;
}
#endif
