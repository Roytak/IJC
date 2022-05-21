/*
*	File: eratosthenes.c
*	IJC-DU1: A)
*	Author: Roman Janota
*	Date: 20. 03. 2022
*	Brief: Sieve of Eratosthenes
*/

#include "bitset.h"
#include "eratosthenes.h"

	/*
		An ancient algorithm for finding all prime numbers up to a given limit
	*/

void Eratosthenes(bitset_t pole) {
	bitset_setbit(pole, 0, 1);
	bitset_setbit(pole, 1, 1);
	unsigned long square = (unsigned long) sqrt(bitset_size(pole));

	for (bitset_index_t i = 2; i < square; i++) {
		if (!(bitset_getbit(pole, i))) {
			for (bitset_index_t j = i * i; j < bitset_size(pole); j += i) {
				bitset_setbit(pole, j, 1);
			}
		}
	}
}