#ifndef HASHDB_H_
#define HASHDB_H_

/*
 * function prototypes
 */
int insertticket(char *, char *, char *, char *, int);
struct vehicle *vehiclelookup(char *, char *);
struct vehicle *sumlookup(char *);
unsigned long dumpindex(uint32_t, unsigned long *);
void dumpdb(void);
void verifydb(void);
void freetickets(void);
unsigned int printvehicle(struct vehicle *);
void largest(void);
int delticket(char *, char *, char *);
int strtoDate(char *, time_t *);
int strtosumid(char *, unsigned long long *);
uint32_t hash(char *);
#endif
