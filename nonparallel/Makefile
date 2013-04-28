CC	= gcc
STD	= -std=gnu9x # Use C99
CFLAGS	= $(STD) -g -Wall -Werror

SRC-MM	= matrix_multiply.c
OBJ-MM	= matrix_multiply.o
EXE-MM	= matrix_multiply

all: $(EXE-MM)

$(EXE-MM): $(OBJ-MM)
	$(CC) -o $(EXE-MM) $(OBJ-MM)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXE-MM) $(OBJ-MM)