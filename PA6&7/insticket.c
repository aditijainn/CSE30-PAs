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

#ifndef MYINSTICKET
TODO(USING THE SOLUTION insticket.c NOT MY CODE)
#else

/*
 * insertticket
 *      add a ticket (summons) to the database
 *
 *      YOU CANNOT USE CALLOC(), only malloc() is allowed.
 *
 *      if the vehicle (plate state) is not in the database then
 *      a new struct vehicle entry must be made for it in the hash table.
 *      New vehicle entries are made at the the FRONT of the collison chain
 *
 *      If the vehicle is already in the hash chain, you only need to add 
 *      a new ticket to the ticket chain for this summons.
 *
 *      Tickets are added to the ticket chain linked to the struct vehicle
 *      at the END of the ticket chain.
 *
 *      Also you must update the tot_fine and cnt_tickets in the struct vehicle
 *      to account for the new summons(ticket) just added
 *  fineTab pointer fine table. maps code number to text description & fine cost 
 *          you use this table to get the amount of the fine when calculating
 *          the tot_fine field in struct vehicle.
 *          example:
 *              struct vehicle *vhpt;
 *              vhpt->tot_fine += fineTab[code].fine;
 *  summ    summons id string to be added
 *          this string needs to be converted to a number to be stored in the
 *          database. This saves space and is faster to compare than a string         
 *          Conversion function is supplied. use example:
 *               unsigned long long summid;
 *               if (strtosumid(summ, &summid, argv) != 0)
 *                  error handling
 *               new_ticket->summons = summid;
 *  plate   plate id string to be added
 *  state   state id string to be added
 *  date    date of summons string
 *          this string needs to be converted to a number to be stored in the
 *          database. This saves space and is faster to compare than a string
 *          The encoding into a number uses Linux time format.
 *          Conversion function is supplied. use example:
 *              time_t dateval;
 *              if (strtoDate(date, &dateval, argv) != 0)
 *                  error handling
 *              new_ticket->date = dateval;
 *  code    summons code integer value used an an index into the fines table
 *
 * returns 0 if ok -1 for all errors
 */

int
insertticket(char *summ, char *plate, char *state, char *date, int code)
{
    unsigned long long summid; // used to convert summ to summid
    time_t dateval;            // used to convert date to dateval

    if (strtosumid(summ, &summid) != 0)
        return -1;

    if (strtoDate(date, &dateval) != 0)
        return -1;

    /*
     * either add ticket to chain or add vehicle and then the ticket
     */
    uint32_t hashval;          // added to htable to find vehicle
    struct vehicle *chain;     // ptr to linkedlist veh exists on
    hashval = hash(plate) % tabsz;
    chain = *(htable + hashval);
    struct vehicle *vehlookupptr; // ptr to vehicle found using vehlookup
    vehlookupptr = vehiclelookup(plate, state);
    struct vehicle *addedveh;     // ptr to added vehicle
    struct ticket *ticketptr;     // ptr to current ticket
    struct ticket *addedticket;   // ptr to added ticket

    if (vehlookupptr == NULL) {   // case for vehicle not found
        if ((addedveh = malloc(sizeof(struct vehicle))) == NULL) {
            fprintf(stderr, "%s: unable to allocate vehicle for summons %s\n", 
	    argv0, summ);         // error handling for malloc
	    return -1;
	}
	if ((state = strdup(state)) == NULL) { 
	    fprintf(stderr, "%s: unable to allocate state for summons %s\n", argv0, summ);
	    return -1;
	}
	if ((plate = strdup(plate)) == NULL) {
	    fprintf(stderr, "%s: unable to allocate plate for summons %s\n", argv0, summ);
	    return -1;
	}
	addedveh->state = state;
	addedveh->plate = plate;
	addedveh->tot_fine = fineTab[code].fine;
	addedveh->cnt_ticket = 1;
	addedveh->next = chain; 
	*(htable + hashval) = addedveh;  // making the vehicle the front
	
	if ((addedticket = malloc(sizeof(struct ticket))) == NULL) {
	    fprintf(stderr, "%s: unable to allocate ticket for summons %s\n", argv0, summ);
	    return -1;                   // error handling for malloc
	}
	addedveh->head = addedticket;
	addedticket->summons = summid;
	addedticket->date = dateval;
	addedticket->code = code;
	addedticket->next = NULL;

    } else {                             // case for vehicle found
        ticketptr = vehlookupptr->head;
        while (ticketptr->next != NULL) {
	    if (ticketptr->summons == summid) {     // case for duplicate summons
	        fprintf(stderr, "%s: duplicate summons %llu\n", argv0, summid);
		return -1;
	    } else {
	       ticketptr = ticketptr->next;
	    }
        }
        if (ticketptr->summons == summid) { // case for last ticket being duplicate
	    fprintf(stderr, "%s: duplicate summons %llu\n", argv0, summid);
	    return -1;
        }
        if (ticketptr->next == NULL) {
    	    if ((addedticket = malloc(sizeof(struct ticket))) == NULL) {
                fprintf(stderr, "%s: unable to allocate ticket for summons %s\n", argv0, summ);                        
	        return -1;               // error handling for malloc
            }
            addedticket->summons = summid;
            addedticket->date = dateval;
	    addedticket->code = code;
	    addedticket->next = NULL;
	    ticketptr->next = addedticket;   // last ticket next set to new ticket
	    vehlookupptr->tot_fine += fineTab[code].fine;
	    vehlookupptr->cnt_ticket += 1;
	}
    }
        		
    /*
     * if you are inserting a ticket and find it is already in the database
     * do not insert it, do the following error message
     * fprintf(stderr,"%s: duplicate summons %llu\n", argv0, summid);
     * then do a return -1;
     */

    return 0;
}
#endif
