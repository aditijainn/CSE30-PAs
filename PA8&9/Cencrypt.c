// version 1.0 11/12/2022
#include <stdio.h>
#include "cipher.h"

#ifdef MYENCRYPT_C
TODO("using Cencrypt.c");

/**
 * function encrypt()
 *
 * Operation: uses the cipher key buffer in
 * bookbuf to encrypt the bytes in iobuf
 * assumes: iobuf & bookbuf have cnt bytes
 * params: *iobuf, *bookbuf, cnt
 * returns: cnt
 */
int
encrypt(char *iobuf, char *bookbuf, int cnt)
{

    int count = 0;                                           // counts # of bytes
    while (count < cnt) {
	unsigned int reverseiobuf = 0;                       // stores reverse iobuf
        for (int i = 0; i < 8; i++) {
	    if ((unsigned int) *(iobuf+count) & (1 << i)) {  // if both bits = 1 after shift
	        reverseiobuf |= (1 << (7-i));     
		// stores the or of 0 and shifted result of 1 by (8 bits - 1 - i)
	    }
	}
	*(iobuf + count) = reverseiobuf ^ (unsigned int) *(bookbuf + count);
	// stores the xor of reverseiobuf and current byte of bookbuf into iobuf's byte
	count++;
    }
    return cnt;
}

#elif defined MYENCRYPT_S
TODO("using encrypt.S");
#else
TODO("using solution encrypt");
#endif
