CC = gcc

CFLAGS = -Wall -I.

DEPS =

OBJ = exercise07.o

%.o: %.c $(DEPS)
	$(CC) -c $(CFLAGS) -o $@ $<

all: exercise07

exercise07: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OBJ) exercise07
