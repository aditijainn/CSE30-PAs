/*
 * Programming assignment 6 sample solution
 * this is excessively commented for quick reads...
 *
 * Usage ./parking -c cvs_file -f fine_file
 *
 * reads the fine table up to get the fines for
 * each type of parking ticket 1-99
 *
 * fine table (csv):
 * code,description,fine
 *
 * read the ticket data in the cvs file into a
 * into a in memory hashed database
 *
 * ticket file (csv):
 * summons_id,state,plate,date,code
 *
 * assumes the above file formats
 * 
 * error handling:
 *     print out error for bad arguments and malformed lines
 *     will drop bad ticket records and run
 *     will not run on a bad fine table
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "parking.h"
#include "hashdb.h"
#include "loaddb.h"
#include "commands.h"

/*
 * global variables used by most of the functions in the program
 */
char *argv0;                /* pointer to argv0 for error messages */
struct vehicle **htable;    /* pointer to hash table */
struct fine *fineTab;       /* table of fines by code 1-99 */
uint32_t tabsz = TABSZ;     /* hash table size */

/*
 * main
 *
 * Arguments: argc, argv
 * 
 * Operation:  driver for in memory ticket database
 *  parses options
 *  open files, then reads up fines, read up ticket data, closes files
 *
 *  Has a simple command line interface; runs until EOF on stdio or q command
 *  see commands.c
 */ 
int 
main(int argc, char **argv)
{
    char *ticknm = NULL;    /* name of ticket data file name */
    char *finenm = NULL;    /* name of fines data file name */
    int silent = 0;         /* silent mode for script testing */
    int opt;                /* option flag returned by getopt */
    char *endptr;           /* for strtol(); ensure entire argument is parsed */
    int retval = EXIT_SUCCESS; /* return value */

    argv0 = *argv; // set global with command name for error printing

    /*
     * parse the command line args.
     * if there was an error, return with EXIT_FAILURE
     */
    while ((opt = getopt(argc, argv, "+d:f:t:s")) != -1) {
        switch (opt) {
        case 'd':
            /*
             * name of ticket data to read up
             */
            ticknm  = optarg;
            break;
        case 'f':
            /*
             * name of fine file to read up
             */
            finenm  = optarg;
            break;
        case 's':
            silent = 1;
            break;
        case 't':
            /*
             * over-ride of hash table size
             */
            errno = 0;
            tabsz = (uint32_t)strtoul(optarg, &endptr, 10);
            if ((*endptr != '\0') || (errno != 0) || (tabsz < MINTABSZ)) {
                fprintf(stderr, "%s: -t operand bad value\n", argv0);
                retval = EXIT_FAILURE;
            }
            break;
        case '?':
        default:
            /*
             * this is the case for error message handle directly by getopt()
             * we just mark we got an error
             */
            retval = EXIT_FAILURE;
            break;
        }
    }

    /*
     * make sure the user specified -d
     */
    if (ticknm == NULL) {
        fprintf(stderr, "%s: -d operand is required\n", argv0);
        retval = EXIT_FAILURE;
    }

    /*
     * make sure the user specified -f
     */
    if (finenm == NULL) {
        fprintf(stderr, "%s: -f operand is required\n", argv0);
        retval = EXIT_FAILURE;
    }

    /*
     * make sure that there are no more args
     */
    if (optind != argc) {
        fprintf(stderr, "%s: Too many args\n", argv0);
        retval = EXIT_FAILURE;
    }

    /*
     * if bad or missing required option, print usage and exit
     */
    if (retval != EXIT_SUCCESS) {
        fprintf(stderr,
            "Usage: %s -d ticket_file -f fine_file [-t size] [-s]\n", argv0);
        return retval;
    }

    /*
     * load the fine table. The fine codes run 1-99
     * so fineTab[1] is the fine for code 1, etc.
     * use calloc() so the table is easy to free if there
     * are errors building it (small table) and keep valgrind
     * happy.
     */
    if ((fineTab = calloc(CODES, sizeof(struct fine))) == NULL) {
        fprintf(stderr,"%s: calloc of fine table failed\n", argv0);
        return EXIT_FAILURE;
    }
    if (readfines(finenm) != 0) {
        freefines();
        free(fineTab);
        return EXIT_FAILURE;
    }
    /*
     * load the ticket table
     * allocate the hash table, then fill it
     */
    if ((htable = calloc(tabsz, sizeof(struct vehicle *))) == NULL) {
        fprintf(stderr,"%s: calloc of ticket table failed\n", argv0);
        freefines();
        free(fineTab);
        return EXIT_FAILURE;
    }
    if (readtickets(ticknm, 0) != 0) {
        freefines();
        free(fineTab);
        freetickets();
        free(htable);
        return EXIT_FAILURE;
    }

    /*
     * interactive commands
     */
    commands(silent, ticknm);

    freefines();
    free(fineTab);
    freetickets();
    free(htable);
    return EXIT_SUCCESS;
}
