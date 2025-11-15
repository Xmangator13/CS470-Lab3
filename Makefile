#compiler to use
CC = gcc
#enables all warnings and optimize for speed
CFLAGS = -Wall -O2

#builds both sjf and rr executables
all: sjf rr
sjf: SJF.c
	$(CC) $(CFLAGS) -o sjf SJF.c
rr: RR.c
	$(CC) $(CFLAGS) -o rr RR.c
#removes compiled binaries
clean:
	rm -f sjf rr
