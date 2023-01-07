#ifndef STATES_H
#define STATES_H
/* 
 * Header file for PA3
 * Author: Aditi 
 */

/*
 * Complete the type definition for DFA states, you do not need an end state
 */
enum typestate {START, BACKSLASH, SLASH, DBLQUOTE, BACKDBLQ, SNGQUOTE, 
	BACKSNGQ, SLCOMMENT, MLCOMMENT, ENDMLCOMMENT };
/*
 *  function prototypes for each state handler of the DFA
 *  Hint you will have to pass the single quote and double quote states
 *       the input plus the starting line number to print the error message
 *       for unterminated literals that see a newline before the ending quote
 *       all other states just need to be passed the input
 */
enum typestate startSTATE(int);          // start state for DFA
enum typestate backslashSTATE(int);      // state if SL comment has backslash
enum typestate slashSTATE(int);          // first state check for comments
enum typestate dblquoteSTATE(int, int);  // state that processes string literals
enum typestate backdblqSTATE(int);       // state if string literal has backslash
enum typestate sngquoteSTATE(int, int);  // state that processes char literals
enum typestate backsngqSTATE(int);       // state if char literal has backslash
enum typestate slcommentSTATE(int);      // state processes single line comments
enum typestate mlcommentSTATE(int);      // state processes multiline comments
enum typestate endmlcommentSTATE(int);   // state checks if ml comment ended
/*
 * global variable set if a state handler sees an error
 * 0 is no error
 * 1 is at least one error
 */
extern int saw_error;

#endif
