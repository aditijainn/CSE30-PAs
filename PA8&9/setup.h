// version 1.0 11/12/2022
#ifndef SETUP_H
#define SETUP_H 1
#ifndef __ASSEMBLER__
int setup(int, char **, int *, FILE **);
#else
.extern setup
#endif
#endif
