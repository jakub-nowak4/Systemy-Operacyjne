CC = gcc
CFLAGS = -Wall -Wextra

all: main producent konsument

main: main.c common.h
	$(CC) $(CFLAGS) -o main main.c

producent: producent.c common.h
	$(CC) $(CFLAGS) -o producent producent.c

konsument: konsument.c common.h
	$(CC) $(CFLAGS) -o konsument konsument.c

clean:
	rm -f main producent konsument *.txt
