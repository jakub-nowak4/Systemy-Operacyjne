CC = gcc
CFLAGS = -Wall -Wextra -std=c11

SRCS = serwer.c klient.c main.c common.c
OBJS = $(SRCS:.c=.o)

all: serwer klient

serwer: serwer.o common.o
	$(CC) $(CFLAGS) -o $@ $^

klient: klient.o common.o
	$(CC) $(CFLAGS) -pthread -o $@ $^

main: main.o common.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c common.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean all
clean:
	rm -f *.o serwer klient main
