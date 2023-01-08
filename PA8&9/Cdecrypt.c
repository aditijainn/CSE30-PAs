// version 1.0 11/12/2022
#include <stdio.h>
#include "cipher.h"

#ifdef MYDECRYPT_C
TODO("using Cdecrypt.c");

/**
 * function decrypt()
 *
 * Operation: uses the cipher key buffer in
 * bookbuf to decrypt the bytes in iobuf
 * assumes: iobuf & bookbuf have cnt bytes
 * params: *iobuf, *bookbuf, cnt
 * returns: cnt
 */
int
decrypt(char *iobuf, char *bookbuf, int cnt)
{

    int count = 0;                                          // counts # of bytes   
    while (count < cnt) {
	unsigned int reverseiobuf = 0;                      // stores reverse of iobuf
	*(iobuf + count) = *(iobuf + count) ^ (unsigned int) *(bookbuf + count);
	// stores the xor of the current byte of bookbuf and iobuf
        for (int i = 0; i < 8; i++) {                       // i < 8 since 8 bits in a byte
	    if ((unsigned int) *(iobuf+count) & (1 << i)) { // if both bits = 1 after shift 
	        reverseiobuf |= 1 << (7-i);
		// stores the or of 0 and shifted result of 1 by (8 bits - 1 - i)
	    }
	}
	*(iobuf + count) = reverseiobuf;                    // stores reverseiobuf into iobuf
	count++;
    }
    return cnt;
}

#elif defined MYDECRYPT_S
TODO("using decrypt.S");
#else
TODO("using solution decrypt");
#endif
