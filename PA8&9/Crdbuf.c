// version 1.0 11/12/2022
#include <stdio.h>
#include "cipher.h"
#include "rdbuf.h"
#ifndef RDBUF_C
TODO("using rdbuf.S");
#else
TODO("using Crdbuf.c");

int
rdbuf(FILE *in, FILE *fpbook, int cnt, char *iobuf, char *bookbuf)
{
    int bytes; /* use in a register no local variables on the stack needed */
   
    /*
     * read the file
     * cnt should be really a size_t but on ARM32 it is an int
     */
    if (feof(in))
        return 0; 

    if (ferror(in))
        return EXIT_FAIL;

    if ((bytes = (int)fread(iobuf, 1, cnt, in)) <= 0)
        return 0;
    /*
     * now read the same number of chars from the bookfile
     * as was read from the input file
     */
    if ((int)fread(bookbuf, 1, bytes, fpbook) != bytes)
        return EXIT_FAIL;

    /*
     * return the number of chars read
     */
    return bytes;
}
#endif
