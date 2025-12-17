CC ?= gcc
CFLAGS ?= -Wall -Wextra -O2

PROGS := producent konsument

.PHONY: all clean

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(PROGS)