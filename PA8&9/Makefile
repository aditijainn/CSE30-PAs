# if you type 'make' without arguments, this is the default
PROG = cipher
all: $(PROG)

# associated object files 
HEAD    = main.h cipher.h rdbuf.h setup.h
OBJ     = Cmain.o Cdecrypt.o Cencrypt.o Crdbuf.o setup.o main.o decrypt.o encrypt.o rdbuf.o

# special libraries
LIB	= libpa8.a
LIBFLAGS =-L ./ $(LIB)

# select the compiler and flags you can over-ride on command line e.g. make DEBUG= 
CC      = gcc
DEBUG	= -ggdb
CSTD	=
WARN	= -Wall -Wextra -Werror
CDEFS	=
CFLAGS	= -I. $(DEBUG) $(WARN) $(CSTD) $(CDEFS) -include SELVERS.h
AR      = ar
ARFLAGS = -rvs 

# some flags to use with assembler tools
ASLIST  = -Wa,-adhln
ASFLAGS =

# how to get an object dump of the target
DUMP   = objdump
DFLAGS = -d

$(OBJ):             $(HEAD) SELVERS.h

# specify how to assemble a .S file
%.o : %.S
	$(CC) $(CFLAGS) $(ASFLAGS)  -c -o $@ $<

# specify how to compile the target
$(PROG):    $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFLAGS) -o $@

.PHONY: clean alltest test1 test2 test3 test4

# get an object dump
dump:       $(PROG)
	$(DUMP) $(DFLAGS) $^


alltest:    test1 test2 test3 test4 test5 test6 test7

test1:      $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest 1

test2:      $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest 2

test3:      $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest 3

test4:      $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest 4

test5:      $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest 5

test6:      $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest 6

test7:      $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest 7

# remove binaries
.PHONY: clean
clean:
	rm -f $(OBJ) $(PROG)
