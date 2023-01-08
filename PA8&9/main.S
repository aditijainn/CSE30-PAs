    // version 1.0 05/22/2022 //
#ifndef MYMAIN_S
#else
    .arch   armv6
    .arm
    .fpu    vfp
    .syntax unified

    // imports
    #include "main.h"
    #include "rdbuf.h"
    #include "setup.h"
    #include "cipher.h"
    .extern fwrite
    .extern stdin
    .extern stdout
    .extern stderr

    .section .rodata
    // do not change these error messages
.Lbdrd:  .string "%s: read failed\n"
.Lbdwr:  .string "%s: write failed\n"

    .text

    //
    // encrypter [-d | -e] -b bookfile
    //
    // int main(int argc, char **argv)
    // int main(r0=argc, r1=argv)

    .global main
    .type   main, %function

    //
    // stack frame layout
    //
    // TODO PA9: complete the following stack frame design
    // You can change or delete any comments in this file
    //
    .equ    FP_OFF,     32                // fp offset in main stack frame
    .equ    FPBOOK,     4+FP_OFF          // FILE * to book file
    .equ    IOBUF,      BUFSZ+FPBOOK      // buffer for input file
    .equ    MODE,       4+IOBUF           // decrypt or encrypt mode
    .equ    BOOKBUF,    BUFSZ+MODE        // buffer for book file
    .equ    ARGV0,      4+BOOKBUF         // save argv[0] for error printing
    //
    // add your local variables here if you need them:
    // NOTICE: Adjust PAD so FRMADD + FP_OFF + 4 divides by 8 EVENLY!
    //
    .equ    PAD,       4+ARGV0            // Stack frame PAD
    .equ    OARG5,     4+PAD              // output arg5 must be at bottom
    .equ    FRMADD,    OARG5-FP_OFF // space in frame for locals+passed args

    // TODO PA9: list how you are using the preserved registers
    // preserved register use
    // r4 used to store temporarily
    // r5 used to store temporarily
    // r6 stores stdin
    // r7 stores FPBOOK
    // r8 stores IOBUF
    // r9 stores BOOKBUF
    // r10 unused

main:
    push    {r4-r10, fp, lr}        // push all the usable preserved registers
    add     fp, sp, FP_OFF          // set frame pointer to frame base
    ldr     r3, =FRMADD             // get space needed for locals+passed args
    sub     sp, sp, r3              // allocate space for locals and passed args 
     
    ldr     r6, [r1]           	    // save argv[0] in argv0, r6 = *argv, r5 = argv0
    ldr     r7, =ARGV0
    str     r6, [fp, -r7]
    
    // at the entry to main() argc is in r0 and argv is in r1.
    ldr     r2, =MODE               // call int setup(r0=argc, r1=argv, r2=*mode, r3=*FPBOOK)
    sub     r2, fp, r2              // Put the address of where mode
    ldr     r3, =FPBOOK             // and FPBOOK are located on main()'s stack and put in r3
    sub     r3, fp, r3              // so setup can fill them in
    bl      setup           
    cmp     r0, EXIT_FAIL           // if setup fails, put EXIT_FAIL in r0 and then branch to .Lfail
    beq     .Lfail

    ldr     r6, =stdin              // set up for main loop
    ldr     r6, [r6]                // save the variables needed in the preserved registers
    ldr     r7, =FPBOOK            
    ldr     r7, [fp, -r7]          
    ldr     r8, =IOBUF
    sub     r8, fp, r8
    ldr     r9, =BOOKBUF
    sub     r9, fp, r9              // r6 = stdin, r7 = FPBOOK, r8 = IOBUF, r9 = BOOKBUF
.Lloop:
    // loop that runs until rdbuf indicates the EOF reached or error
    mov     r0, r9
    ldr     r4, =OARG5
    str     r0, [fp, -r4]           // address of bookbuf at offset OARG5 on the stack
    mov     r3, r8
    mov     r2, BUFSZ
    mov     r1, r7
    mov     r0, r6
    bl      rdbuf                   // int rdbuf(r0=stdin, r1=fpbook, r2=BUFSZ, r3=iobuf,OARG5=bookbuf)
    cmp     r0, 0
    blt     .Lerrorread             // if return less than 0, error print to stderr .Lbdrd, and go to .Ldone
    cmp     r0, 0
    beq     .Ldone                  // if r0 on return from rdbuf has a 0 in r0 we are done, branch to .Ldone
    ldr     r4, =MODE
    ldr     r4, [fp, -r4]
    mov     r2, r0                  // store cnt
    mov     r1, r9
    mov     r5, r0                  // store cnt
    mov     r0, r8
    cmp     r4, ENCRYPT_MODE        // check the mode flag and call either encrypt or decrypt
    bne     .Lelse
    bl      encrypt                 // calls encrypt then branches to fwrite
    b       .Lfwrite
.Lelse:
    bl      decrypt                 // else calls decrypt then branches to fwrite
    b       .Lfwrite
.Lfwrite:
    mov     r4, r5                  // store cnt
    ldr     r5, =stdout             // get stdout
    ldr     r5, [r5]
    mov     r3, r5                  // store stdout in r3
    mov     r2, r0
    mov     r1, 1
    mov     r0, r8
    bl      fwrite                  // fwrite(r0=iobuf, r1=1, r2=cnt, r3=*stdout)
    cmp     r0, r4                  
    beq     .Lloop                  // if cnt characters written go to .Lloop (write is ok)
    
    ldr     r0, =stderr
    ldr     r0, [r0]
    ldr     r1, =.Lbdwr             // othewise error, print to stderr .Lbdwr and fall through to .Ldone
    ldr     r2, =ARGV0
    ldr     r2, [fp, -r2]
    bl      fprintf
    mov     r0, r7
    b       .Ldone
    
.Lfail:
    // print EXIT_FAILURE and fall through to .Lexit
    mov     r0, EXIT_FAILURE
    b       .Lexit

.Ldone:
    // normal exit, call fclose of fpbook and fall through to .Lexit
    mov     r0, r7
    bl      fclose
    b       .Lexit

.Lerrorread:
    // print to stderr .Lbdrd and fall through to .Ldone
    ldr     r0, =stderr
    ldr     r0, [r0]
    ldr     r1, =.Lbdrd
    ldr     r2, =ARGV0
    ldr     r2, [fp, -r2]
    bl      fprintf               
    mov     r0, EXIT_FAILURE
    b       .Ldone

.Lexit:
    sub     sp, fp, FP_OFF
    pop     {r4-r10, fp, lr}
    bx      lr

    .size   main, (. - main)
    .section .note.GNU-stack,"",%progbits
.end
#endif
