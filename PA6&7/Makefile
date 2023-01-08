# if you type 'make' without arguments, this is the default
PROG = parking
all: $(PROG)

# associated object files 
HEAD    = commands.h hashdb.h misc.h token.h parking.h
OBJ     = main.o loaddb.o commands.o insticket.o delticket.o vehlookup.o freetickets.o \
          subs.o largest.o sumlookup.o

# special libraries
LIB	= libpa6.a
LIBFLAGS =-L ./ $(LIB)

# select the compiler and flags you can over-ride on command line e.g. make DEBUG= 
CC      = gcc
DEBUG	= -ggdb
CSTD	=
WARN	= -Wall -Wextra -Werror
CDEFS	=
CFLAGS	= -I. $(DEBUG) $(WARN) $(CSTD) $(CDEFS) -include SELVERS.h

$(OBJ):             parking.h hashdb.h SELVERS.h
command.o:          commands.h loaddb.h
main.o:             loaddb.h commands.h
loaddb.o:           loaddb.h token.h

# specify how to compile the target
$(PROG):	$(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFLAGS) -o $@

.PHONY: clean emptydb demodb alltest testA testB testC testD testV1 testV2 testP

emptydb:  $(PROG)
	./parking -t3 -f in/Fines.csv -d in/Empty.csv

demodb:   $(PROG)
	./parking -t3 -f in/Fines.csv -d in/Tiny.csv

LISTA   = 1 2 DUP
LISTB   = 3 4
LISTC   = 5
LISTD   = 6
LISTV1  = V1 
LISTV2  = V2 
LISTP   = P

alltest:   testA testV1 testB testC testD testV2

testA:      $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest $(LISTA)

testB:      $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest $(LISTB)

testC:      $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest $(LISTC)

testD:      $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest $(LISTD)

testV1:      $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest $(LISTV1)

testV2:      $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest $(LISTV2)

testP:       $(PROG)
	@echo
	@echo "****** starting $@ *******"
	-./runtest $(LISTP)

# remove binaries
clean:
	rm -f $(OBJ) $(PROG)
