# if you type 'make' without arguments, this is the default
PROG    = omit
all:    $(PROG)

# Tell make about the file dependecies
HEAD	= states.h 
OBJ     = states.o omit.o

# special libraries This can be blank
LIB     =

# select the compiler and flags
# you can over-ride these on the command line e.g. make DEBUG= 
CC      = gcc
DEBUG	= -ggdb
CSTD	=
WARN	= -Wall -Wextra -Werror
CDEFS	=
CFLAGS	= -I. $(DEBUG) $(WARN) $(CSTD) $(CDEFS)

$(OBJ):	$(HEAD)

# specify how to compile the target
$(PROG):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $@

#Specify the test number to test in order
LIST    = 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
testlist:    $(PROG)
	./runtest $(LIST)

# remove binaries
.PHONY: clean 
clean:
	rm -f $(OBJ) $(PROG)

