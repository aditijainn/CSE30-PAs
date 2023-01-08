// version 1.0 11/12/2022
#ifndef CIPHER_H
#define CIPHER_H 1
#define ENCRYPT_MODE	1
#define DECRYPT_MODE	0
#define	EXIT_OK		    0
#define	EXIT_FAIL	    -1
#define BITS            8
#ifndef __ASSEMBLER__
int encrypt(char *, char *, int);
int decrypt(char *, char *, int);
#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("WARNING - " #x))
#else
.extern encrypt
.extern decrypt
#endif
#endif
