#ifndef PARKING_H
#define PARKING_H
#define TABSZ 8171  /* default hash table size a prime number */
#define MINTABSZ 1  /* Smallest allowable hash table size */

#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("TODO - " #x))

/*
 * fine description by code (table index is code)
 * given a summons code this maps to a description and fine amount
 */
struct fine {
    char *desc;             /* text description of code */
    unsigned int fine;      /* value of the fine in $ */
};
#define CODES 100   /* number of fine codes + 1 */

/*
 * a specific summons
 * Note: for this PA summons as a long is ok, but it should be bigger
 *       also time_t on 32-bit OS may wrap in 2038....
 */
struct ticket {
    unsigned long long summons;/* summons or ticket id */
    time_t date;            /* date summons was issued */
    unsigned int code;      /* fine code 1-99 */
    struct ticket *next;    /* pointer to next ticket */
};

/*
 * a vehicle that has at least one summons
 */
struct vehicle {
    char *state;            /* state on license plate */
    char *plate;            /* id on license plate */
    unsigned int tot_fine;  /* summary field; all tickets */
    unsigned int cnt_ticket;/* number of tickets unpaid */
    struct vehicle *next;   /* pointer to next vehicle on hash chain */
    struct ticket *head;    /* pointer to first ticket; add tickets to end! */
};

/* 
 * global variable declaration for error message printing
 */
extern char *argv0;                /* for error message printing */
extern struct vehicle **htable;    /* pointer to hash table */
extern struct fine *fineTab;       /* table of fines by code 1-99 */
extern uint32_t tabsz;             /* hash table size */
#endif
