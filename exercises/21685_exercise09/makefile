 #
# By convention, macros are used to specify the compiler to use and options for
# the compiler command, dependencies and intermediate (object) files.
#

# CC is the compiler to use (gcc)
CC = gcc

# CFLAGS contains options to pass to the compiler. Tells the compiler to look for
# header files in the current directory in addition to standard system locations
# (e.g. /usr/include).  The -Wall option tells the compiler to print all warnings.
CFLAGS = -Wall -I.

# DEPS is for dependencies (e.g. local header files)
DEPS = 

# OBJ lists all object files (.o files) that the executable target depends on
OBJ = exercise09.o

# This is a general rule that creates intermediate files (creates .o files from .c
# files).  A new .o file needs to be created when the corresponding .c file is
# changed or when a dependency is changed.
%.o: %.c $(DEPS)
	$(CC) -c $(CFLAGS) -o $@ $<

# The first specific target, which "depends" on whatever the exercise09 target does
all: exercise09

# The exercise09 target, which depends on the intermediate files.  This compiles the
# program called exercise09
exercise09: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

# A clean target that removes all files created by this makefile
clean:
	rm -f $(OBJ) exercise09
