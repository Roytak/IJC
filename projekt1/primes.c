/*
*   File: primes.c
*   IJC-DU1: A)
*   Author: Roman Janota
*   Date: 20. 03. 2022
*   Brief: Prints 10 closest primes numbers to 300 million and not greater
*/

#include "bitset.h"
#include "eratosthenes.h"
#include <time.h>

void Eratosthenes(bitset_t set);

    /*
        Calculates the prime numbers to 300 millions and measures the time it takes
    */
#define test 1
#ifdef USE_INLINE
#undef test
#define test 2
#endif

int main() {
    clock_t start = clock();
    bitset_create(prime_numbers, 300);    
    Eratosthenes(prime_numbers);
    unsigned long primes_array[10];
    bitset_index_t i = bitset_size(prime_numbers) - 1;
    int counter = 0;
    while (counter < 10) {
        if (!(bitset_getbit(prime_numbers, i))) {
            primes_array[counter] = i;
            counter++;
        }
        i--;
    }

    for (int j = 9; j >= 0; j--) {
        printf("%lu\n", primes_array[j]);
    }

    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}