/*
 * State handler routines for PA
 * one function for each state of the DFA
 *
 * Author: Aditi 
 */

#include <stdio.h>
#include "states.h"

/*
 * global flag set by state handlers if they see an error
 * 0 is no error
 * 1 is at least 1 error
 */
int saw_error = 0;

/*
 * Takes in char at a time and diverts 
 * to correcct next state
 */
enum typestate startSTATE(int c)
{
    if (c == '/') {
        return SLASH;
    } else if( c == '\"') {
        putchar(c);
	return DBLQUOTE;
    } else if (c == '\'') {
	putchar(c);
	return SNGQUOTE;
    } else if (c == '\n') {
	putchar('\n');
	return START;
    } else {
        putchar(c);
        return START;
    }
}

/*
 * Checks if char after / is a comment
 * and diverts it to the correct state
 * to handle it
 */
enum typestate slashSTATE(int c)
{
    if (c == '"') {
	putchar('/');
	putchar(c);
        return DBLQUOTE;
    } else if (c == '\'') {
	putchar('/');
	putchar(c);
	return SNGQUOTE;
    } else if (c == '/') {
	putchar(' ');
	return SLCOMMENT;
    } else if (c == '*') {
	putchar(' ');
	return MLCOMMENT;
    } else if (c == '\\') {
	return BACKSLASH;
    } else {
	putchar('/');
	putchar(c);
        return START;
    }
}

/*
 * Handles what comes after the
 * escape char \ for single line 
 * comments
 */
enum typestate backslashSTATE(int c)
{
    if(c == '\n') {
        putchar('\n');
        return START;
    } else {
	putchar(c);
        return START;
    }
}

/*
 * Handles how to process string literals
 * Uses  c and startline to print errors
 * if needed
 */
enum typestate dblquoteSTATE(int c, int startline)
{
    if (c == '\n') {
	putchar('\n');
	saw_error = 1;
        fprintf(stderr, "Error: line %d: unterminated quote(\")\n", startline);
    	return START;
    } else if (c == '\\') {
	putchar(c);
        return BACKDBLQ;
    } else if (c == '"') {
	putchar(c);
	return START;
    } else {
	putchar(c);
        return DBLQUOTE;
    }
}

/*
 * Handles how to process char after
 * backslash in a string literal
 */
enum typestate backdblqSTATE(int c)
{
    if(c == '\n') {
        putchar('\n');
	return DBLQUOTE;
    } else {
	putchar(c);
	return DBLQUOTE;
    }
}

/*
 * Handles how to process char literals 
 * Uses c and startline to print errors if needed
 */
enum typestate sngquoteSTATE(int c, int startline)
{
    if (c == '\n') {
	putchar('\n');
        saw_error = 1;
        fprintf(stderr, "Error: line %d: unterminated quote(\')\n", startline);
	return START;
    } else if (c == '\\') {
	putchar(c);
	return BACKSNGQ;
    } else if (c == '\'') {
	putchar(c);
        return START;
    } else {
        putchar(c);
        return SNGQUOTE;
    }
}

/*
 * Handles how to process char after
 * backslash in char literal
 */
enum typestate backsngqSTATE(int c)
{
    if (c == '\n') {
	putchar('\n');
        return SNGQUOTE;
    } else {
	putchar(c);
	return SNGQUOTE;
    }
}

/*
 * Handles how to process single line
 * comments
 */
enum typestate slcommentSTATE(int c)
{
    if (c == '\n') {
        putchar('\n');
	return START;
    } else if (c == '\\') {
	return BACKSLASH;
    } else {
        return SLCOMMENT;
    }
}

/*
 * Handles how to process multiline 
 * comments
 */
enum typestate mlcommentSTATE(int c)
{
    if (c == '\n') {
	putchar('\n');
        return MLCOMMENT;
    } else if (c == '*') {
	return ENDMLCOMMENT;
    } else {
        return MLCOMMENT;
    }
}

/*
 * Handles if multiline comment is ended
 * or is continued
 */
enum typestate endmlcommentSTATE(int c) 
{
    if (c == '/') {
	return START;
    } else {
	return MLCOMMENT;
    }
}

