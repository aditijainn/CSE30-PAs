// version 1.0 11/12/2022
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "rdbuf.h"
#include "setup.h"
#include "cipher.h"
#ifndef MAIN_C
TODO("using main.s");
#else
TODO("using Cmain.c");
int
main(int argc, char **argv)
{
    /*
     * do not change the definition order of these local variables
     */
    FILE *fpbook;
    char iobuf[BUFSZ];
    int mode;
    char bookbuf[BUFSZ];
    char *argv0;
    int cnt; /* do not put on stack, use a register for this */

    /*
     * parse the command line arguments, set mode (encrypt or decrypt)
     * and open the book file
     */
    argv0 = *argv;
    if (setup(argc, argv, &mode, &fpbook) == EXIT_FAIL)
        return EXIT_FAILURE;

    /*
     * read the input and book file until EOF on the input file
     * Either encrypt or decrypt
     * then write it out.
     */ 
    while ((cnt = rdbuf(stdin, fpbook, BUFSZ, iobuf, bookbuf)) > 0) {
        if (mode == ENCRYPT_MODE)
            cnt = encrypt(iobuf, bookbuf, cnt);
        else
            cnt = decrypt(iobuf, bookbuf, cnt);
        if (fwrite(iobuf, 1, cnt, stdout)  != (size_t)cnt) {
            fprintf(stderr, "%s: write failed\n", argv0);
            fclose(fpbook);
            return EXIT_FAILURE; 
        }
    }
    /*
     * close the book file
     */
    fclose(fpbook);
    if (cnt == EXIT_FAIL) {
        fprintf(stderr, "%s: read failed\n", argv0);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
#endif
