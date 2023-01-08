# if you type 'make' without arguments, this is the default
PROG    = extract
all:    $(PROG)

# Tell make about the file dependencies
HEAD	= token.h
OBJ     = token.o main.o

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

#Specify the test number to test at a time
LIST1    = 1 2 
LIST2    = 3 4 
LIST3    = 5 
LIST4    = 6 7 

.PHONY: clean alltest testA testB testC testD

alltest:    testA testB testC testD

testA:      $(PROG)
	-./runtest -c3 $(LIST1)

testB:      $(PROG)
	-./runtest -c4 $(LIST2)

testC:      $(PROG)
	-./runtest -c43 $(LIST3)

testD:      $(PROG)
	-./runtest -c3 $(LIST4)

# remove binaries
clean:
	rm -f $(OBJ) $(PROG)

