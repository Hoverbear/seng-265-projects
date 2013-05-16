CC=gcc
CFLAGS=-c -g -ansi -Wall -DDEBUG
LDFLAGS=

all: s265fmt3 driver

s265fmt3: s265fmt3.o uvic_formatter.o
	$(CC) $(LDFLAGS) s265fmt3.o uvic_formatter.o -o s265fmt3

driver: driver.o uvic_formatter.o
	$(CC) $(LDFLAGS) driver.o uvic_formatter.o -o driver

driver.o: driver.c uvic_formatter.h
	$(CC) $(CFLAGS) driver.c

s265fmt3.o: s265fmt3.c uvic_formatter.h
	$(CC) $(CFLAGS) s265fmt3.c

uvic_formatter.o: uvic_formatter.c uvic_formatter.h
	$(CC) $(CFLAGS) uvic_formatter.c

clean:
	/bin/rm -f s265fmt3 driver s265fmt3.o driver.o uvic_formatter.o
