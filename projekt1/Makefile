CC=gcc
CFLAGS=-g -O2 -std=c11 -pedantic -Wall -Wextra

DEPS = bitset.h error.h ppm.h eratosthenes.h

LIBS = lm

TARGET = steg-decode primes primes-i

all: $(TARGET)

steg-decode: steg-decode.o eratosthenes.o ppm.o error.o
	$(CC) $(CFLAGS) -o $@ $^ -$(LIBS)

steg-decode.o: steg-decode.c bitset.h eratosthenes.h error.h
	$(CC) $(CFLAGS) -c $<

primes: primes.o eratosthenes.o error.o
	$(CC) $(CFLAGS) -o $@ $^ -$(LIBS)

primes.o: primes.c bitset.h eratosthenes.h error.h
	$(CC) $(CFLAGS) -c $<		

primes-i: primes-i.o eratosthenes.o error.o
	$(CC) $(CFLAGS) -DUSE_INLINE -o $@ primes.o eratosthenes.o error.o -$(LIBS)

primes-i.o: primes.c bitset.h eratosthenes.h error.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c $<

eratosthenes.o: eratosthenes.c eratosthenes.h
	$(CC) $(CFLAGS) -c $<

ppm.o: ppm.c ppm.h
	$(CC) $(CFLAGS) -c $<

error.o: error.c error.h
	$(CC) $(CFLAGS) -c $<					

run: primes primes-i
	./primes & ./primes-i

.PHONY: clean	

clean:
	rm *.o