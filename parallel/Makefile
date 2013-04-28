CC	= gcc
STD	= -std=gnu9x # Use C99
CFLAGS	= $(STD) -g -Wall -Werror
C_OMP	= -fopenmp

SRC-MM	= matrix_multiply_parallel.c
OBJ-MM	= matrix_multiply_parallel.o
EXE-MM	= matrix_multiply_parallel

all: $(EXE-MM)

$(EXE-MM): $(SRC-MM)
	$(CC) $(C_OMP) $(CFLAGS) -o $(EXE-MM) $(SRC-MM)

clean:
	rm -f $(EXE-MM)