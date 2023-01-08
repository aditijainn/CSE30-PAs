
/* PA5 Part1 action:
 * (1) delete this put your token.c from PA4 here
 * (2) modify your PA4 code to supported quoted fields as described in the
 * writeup.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "token.h"

/*
 * token
 * 
 * usage:   input buffer in dsv format, builds table of pointers to each field
 * args:
 *  buf     DSV data record stored in an array of characters, '\0' terminated
 *  delim   the field delimiter             
 *  cnt     number of data fields that a proper data record has
 *  ptable  points at array of pointers each element points at a data field
 *  lineno  line number of this record for printing error messages
 *  argv0   name of program used when printing errors
 * returns:
 *          0 if no errors founds
 *         -1 otherwise
 */
int
token(char *buf, char delim, int cnt, char **ptable, unsigned long lineno,
            char *argv0)
{
char **endptr = ptable + cnt;
while((ptable < endptr) && (*buf != '\0')) {
    *ptable++ = buf;               // creates pointer
    if (*buf == '\"') {
	buf++;
        while (*buf != '\0') {
	    if (*buf == '\"') {
	        buf++;
	        if (*buf == delim) {
                    *buf = '\0';
	            buf++;
	            break;
	        } else if (*buf == '\n') {
	            *buf = '\0';
		    buf++;
		    break;
		} else if (*buf == '\"') {
		    buf++;
		} else {
		    fprintf(stderr, "%s: drop line %lu, quoted field not terminated\n", 
		    argv0, lineno);
		    return -1;
		}
	    } else if (*buf == '\n') {
		fprintf(stderr, "%s: drop line %lu, quoted field not terminated\n",
		argv0, lineno);
		return -1;
	    } else {
		buf++;
	    }
	} 
    } else {  	
        while(*buf != '\0') {
            if (*buf == delim) {       // case for delimiter
	        *buf = '\0';
	        buf++;
	        break;
	    } else if (*buf == '\n') { // case for new line
	        *buf = '\0';
	        buf++;
	        break;
	    } else if (*buf == '\"') { // case for finding 
		fprintf(stderr, "%s: drop line %lu, \" in unquoted field\n", 
		argv0, lineno);
		return -1;
	    } else {
	        buf++;
	    }
        }
    }
}

if (*buf != '\0' && ptable == endptr) {  // case for too any columns
    fprintf(stderr, "%s: drop line %lu, too many columns\n", argv0, lineno);
    return -1;
}

if (ptable < endptr && *buf == '\0') {   // case for too few columns
    fprintf(stderr, "%s: drop line %lu, too few columns\n", argv0, lineno);
    return -1;
}

return 0;
}

/*
 * hint at the start of each field check if the first character in the field
 * is a double quote, if not do the code processing from PA4
 * if the first character is a double code add code to process the quoted field.
 * it is often easier to just have two disinct sections of code one for
 * unquoted fields and one for quoted ifields than to try and merge them into
 * one code body and use flag variables. the logic gets hard to read
 * and hard to debug when merged. This is just a suggestion.
 */ 

/*
 * delete this comment. Here is the additional code snippet for printing 
 * error messages when handling quoted fields
 * fprintf(stderr, "%s: drop line %lu, quoted field not terminated\n",
 *          argv0, lineno);
 *
 * continue to use the error messages you had in PA4.
 */
