CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -static -s -fstack-protector-strong -D_FORTIFY_SOURCE=2 -Os
LDFLAGS = -Wl,-z,relro,-z,now
DESTDIR = /usr/local

all: netshell netshell-multi

netshell: netshell.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o netshell netshell.c

netshell-multi: netshell-multi.c
	$(CC) $(CFLAGS) $(LDFLAGS) -pthread -o netshell-multi netshell-multi.c

netshell.1: netshell.man
	man -t netshell.man > netshell.1

netshell-multi.1: netshell-multi.man
	man -t netshell-multi.man > netshell-multi.1

.PHONY: clean install

clean:
	rm -f netshell netshell-multi netshell.1 netshell-multi.1

install: all netshell.1 netshell-multi.1
	install -m 0755 netshell $(DESTDIR)/bin/
	install -m 0755 netshell-multi $(DESTDIR)/bin/
	install -m 0644 netshell.1 $(DESTDIR)/share/man/man1/
	install -m 0644 netshell-multi.1 $(DESTDIR)/share/man/man1/
