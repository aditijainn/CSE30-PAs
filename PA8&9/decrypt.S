#ifndef MYDECRYPT_S
#else
// version 1.0 11/12/2022
    .arch armv6
    .arm
    .fpu vfp
    .syntax unified

    #include "cipher.h"

    .text     // start of text segment

    //////////////////////////////////////////////////
    // int decrypt(char *iobuf, char *bookbuf, int cnt)
    // decrypts iobuf using bookbuf; result in iobuf
    //////////////////////////////////////////////////
    .global decrypt
    .type   decrypt, %function
    .equ    FP_OFF, 28

decrypt:
    push    {r4-r9, fp, lr}
    add     fp, sp, FP_OFF
    // do not alter anything above this line
    // r0 contains char *iobuf
    // r1 contains char *bookbuf
    // r2 contains cnt
    // r3 contains count
    // r4 contains i used in the for loop condition
    // r5 contains *(iobuf + count)
    // r6 used for arithmetic and shift data storing
    // r7 used for condition in if statement
    // r8 used to store shifted bit 'or'ed with reverseiobuf
    // r9 contains reverseiobuf

    cmp     r2, 0               // if buffer empty we are done
    ble     .Ldone

    // your code here
    mov     r3, 0               // count = 0
    cmp     r3, r2              // count < cnt condition
    bge     .Lendw              
.Lwhile:
    // process one byte at a time
    ldrb    r4, [r0, r3]        // r4 stores *(iobuf + count)
    ldrb    r6, [r1, r3]        // r6 stores *(bookbuf + count)
    eor     r5, r4, r6          // r5 stores xor of reverseiobuf & *(bookbuf + count)
    strb    r5, [r0, r3]        // store r5 into *(iobuf + count)
    mov     r9, 0               // reverseiobuf = 0
    mov     r4, 0               // i variable in for loop = 0
.Lfor:
    // process one bit at a time
    ldrb    r5, [r0, r3]        // store *(iobuf + count) in r5
    mov     r6, 1               
    lsl     r6, r6, r4          // shift 1 by i
    and     r7, r5, r6          // results in 1 both bits = 1
    cmp     r7, 0               // if r7 not equal to 0
    beq     .Lfalse             
    rsb     r6, r4, BITS-1      // 7 - i
    mov     r8, 1               
    lsl     r8, r8, r6          // shift 1 by 7-i
    orr     r9, r9, r8          // reverseiobuf = reverseiobuf or shifted result
.Lfalse: 
    // process if r7 = 0
    add     r4, r4, 1           // i++
    cmp     r4, BITS
    blt     .Lfor               // back to for loop if i < 8
.Lendf:
    // end of for loop
    strb    r9, [r0, r3]        // store reverseiobuf into *(iobuf + count)
    add     r3, r3, 1           // count++
    cmp     r3, r2              // while loop condition check
    blt    .Lwhile
.Lendw:                         
    // end of while loop
    // do not alter anything below this line
.Ldone:
    mov     r0, r2              // return cnt processed
    sub     sp, fp, FP_OFF
    pop     {r4-r9, fp, lr}
    bx      lr

    .size decrypt, (. - decrypt)
    .section .note.GNU-stack,"",%progbits
.end
#endif
