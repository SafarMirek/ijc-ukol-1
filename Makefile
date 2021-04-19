LC_ALL = cs_CZ.utf8
CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -O2
LDFLAGS = -g -std=c11 -pedantic -Wall -Wextra
LDLIBS  = -lm

all: primes primes-i steg-decode

primes: primes.o eratosthenes.o error.o

primes-i: primes-i.o eratosthenes-i.o error.o

steg-decode: steg-decode.o error.o ppm.o eratosthenes.o

error.o: error.h error.c

primes.o: primes.c bitset.h error.h

primes-i.o: primes.c bitset.h error.h
	$(CC) -c $(CFLAGS) -DUSE_INLINE primes.c -o $@

eratosthenes.o: eratosthenes.c bitset.h error.h

eratosthenes-i.o: eratosthenes.c bitset.h error.h
	$(CC) -c $(CFLAGS) -DUSE_INLINE eratosthenes.c -o $@

steg-decode.o: steg-decode.c error.h ppm.h eratosthenes.h bitset.h

ppm.o: ppm.h ppm.c

run: primes primes-i
	./primes
	./primes-i

clear:
	rm -f *.o primes primes-i steg-decode

package:
	zip xsafar23.zip *.c *.h Makefile

.PHONY: all run clear