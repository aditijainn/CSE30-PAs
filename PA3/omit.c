/*
 * CSE Programming assignment 3 
 * Author: Aditi
 *
 * What this program does:
 *      remove c comments from a source file and write to stdout
 *      comments are replaced with a single space
 *      handles single and double quoted sequences
 *      all newlines are preserved
 *
 * error handling:
 *      prints starting line for unterminated comments or quote sequences
 *      to stderr
 *
 * return either:
 *      EXIT_SUCCESS if no errors
 *      EXIT_FAILURE if errors
 *      
 */

#include <stdio.h>
#include <stdlib.h>
#include "states.h"
#define CNT 1   /* start count lines in input at CNT */

int
main(void)
{
    int c;              /* input char  */
    int linecnt = CNT;  /* counts line in input */
    int startline = CNT;/* starting line number for comment/quote */
    enum typestate state = START;  /* initial state of DFA */

    /*
     * Processes chars one at a time until EOF, switches each to each 
     * state based on char processed
     */
     while ((c = getchar()) != EOF) {
         switch (state) {
	 case START:
	     state = startSTATE(c);
	     startline = linecnt;
	     break;
	 case BACKSLASH:
	     state = backslashSTATE(c);
	     break;
	 case SLASH:
	     state = slashSTATE(c);
	     break;
	 case DBLQUOTE:
             state = dblquoteSTATE(c, startline);
	     break;
	 case BACKDBLQ:
	     state = backdblqSTATE(c);
	     break;
	 case SNGQUOTE:
	     state = sngquoteSTATE(c, startline);
	     break;
	 case BACKSNGQ:
	     state = backsngqSTATE(c);
	     break;
	 case SLCOMMENT:
	     state = slcommentSTATE(c);
	     break;
	 case MLCOMMENT:
	     state = mlcommentSTATE(c);
             break;
	 case ENDMLCOMMENT:
	     state = endmlcommentSTATE(c);
	     break;
	 default:
	     fprintf(stderr, "Error: DFA state not handled\n");
	     return EXIT_FAILURE;
	 }
	 if (c == '\n') {
             linecnt++;
	 }
     }    
    /*
     * Checks for error conditions based on the state we ended in
     * then returns correct exit based on errors
     */
     if (state == START && saw_error == 0) {
	 return EXIT_SUCCESS;
     } else if (state == MLCOMMENT) {
	 fprintf(stderr, "Error: line %d: unterminated comment\n", startline);
	 return EXIT_FAILURE;
     } else if (state == DBLQUOTE) {
	 fprintf(stderr, "Error: line %d: unterminated quote(\")\n", startline);
	 return EXIT_FAILURE;
     } else if (state == SNGQUOTE) {
	 fprintf(stderr, "Error: line %d: unterminated quote(\')\n", startline);
	 return EXIT_FAILURE;
     } else {
	 return EXIT_FAILURE;
     }
}
