/*
*	File: bitset.h
*	IJC-DU1: A)
*	Author: Roman Janota
*	Date: 20. 03. 2022
*	Brief: A header file that defines macros and inline functions for manipulating with bits
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <string.h>

typedef unsigned long *bitset_t;

typedef unsigned long bitset_index_t;

#define UNSIGNED_LONG_SIZE_IN_BITS (sizeof(unsigned long)*(CHAR_BIT))

#define MIN_BITSET_SIZE 2   /** to assure, that any bitset has at least 2 unsigned longs, since the 1st ul stores the bitset's size*/

void error_exit(const char *fmt, ...);

#ifndef USE_INLINE

	/*
		Statically declares an unsigned long array, initializes it to 0 and sets the 1st element to it's size
	*/

	#define bitset_create(jmeno_pole, velikost) \
		static_assert(velikost > 0, "The size of the bit array has to be greater than 0."); \
		unsigned long jmeno_pole[(velikost - 1)/(UNSIGNED_LONG_SIZE_IN_BITS) + MIN_BITSET_SIZE] = {velikost}

	/*
		Dynamically allocates an unsigned long array, initializes it to 0 and sets the 1st element to it's size
	*/	

	#define bitset_alloc(jmeno_pole, velikost) \
		assert(velikost > 0); \
		bitset_t jmeno_pole = calloc((velikost - 1)/(UNSIGNED_LONG_SIZE_IN_BITS) + MIN_BITSET_SIZE, sizeof(unsigned long)); \
		jmeno_pole[0] = velikost; \
		if (jmeno_pole == NULL) { \
			error_exit("bitset_alloc: Chyba alokace paměti"); \
		}

	/*
		Frees the allocated memory of a dynamically allocated bitset
	*/

	#define bitset_free(jmeno_pole) \
		if (jmeno_pole != NULL) \
			free(jmeno_pole)

	/*
		Gets the size of the bitset stored in the 1st unsigned long of the array
	*/

	#define bitset_size(jmeno_pole) \
		jmeno_pole[0]

	/*
		Sets the bit to expression (0 or 1), on the index of the array
	*/
		
	#define bitset_setbit(jmeno_pole, index, vyraz) \
		do { \
			if (index >= jmeno_pole[0]) \
				error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (unsigned long) index, (unsigned long) jmeno_pole[0]); \
			else if (vyraz) { \
					jmeno_pole[1 + (index)/(UNSIGNED_LONG_SIZE_IN_BITS)] |= (1UL << ((index) % (UNSIGNED_LONG_SIZE_IN_BITS))); \
			} \
			else { \
				jmeno_pole[1 + (index)/(UNSIGNED_LONG_SIZE_IN_BITS)] &= ~(1UL << ((index) % (UNSIGNED_LONG_SIZE_IN_BITS))); \
			} \
		} while (0)		
	/*
		Gets the bit on the index of the aray
	*/

	#define bitset_getbit(jmeno_pole, index) \
		(((index) >= (jmeno_pole[0])) ? (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long) index, (unsigned long) jmeno_pole[0])) : (void) 0) , \
		jmeno_pole[1 + (index)/(UNSIGNED_LONG_SIZE_IN_BITS)] & (1UL << ((index) % (UNSIGNED_LONG_SIZE_IN_BITS))) ? (1) : (0)
	
	/*
		Inline function version of previous macros
	*/

#else
	extern inline void bitset_free(bitset_t jmeno_pole);
	extern inline unsigned long bitset_size(bitset_t jmeno_pole);
	extern inline void bitset_setbit(bitset_t jmeno_pole, unsigned long index, long long vyraz);
	extern inline unsigned int bitset_getbit(bitset_t jmeno_pole, unsigned long index);

	#define bitset_create(jmeno_pole, velikost) \
		static_assert(velikost > 0, "The size of the bit array has to be greater than 0."); \
		unsigned long jmeno_pole[(velikost - 1)/(UNSIGNED_LONG_SIZE_IN_BITS) + MIN_BITSET_SIZE] = {velikost}

	#define bitset_alloc(jmeno_pole, velikost) \
		assert(velikost > 0); \
		bitset_t jmeno_pole = calloc((velikost - 1)/(UNSIGNED_LONG_SIZE_IN_BITS) + MIN_BITSET_SIZE, sizeof(unsigned long)); \
		jmeno_pole[0] = velikost; \
		if (jmeno_pole == NULL) { \
			error_exit("bitset_alloc: Chyba alokace paměti"); \
		} 

	inline void bitset_free(bitset_t jmeno_pole) {
		if (jmeno_pole != NULL) 
			free(jmeno_pole);
	}

	inline unsigned long bitset_size(bitset_t jmeno_pole) {
		return jmeno_pole[0];
	}

	inline void bitset_setbit(bitset_t jmeno_pole, unsigned long index, long long vyraz) {
		if (index >= jmeno_pole[0]) {
			error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (unsigned long) index, (unsigned long) jmeno_pole[0]);
		}
		else if (vyraz) { 
			jmeno_pole[1 + (index)/(UNSIGNED_LONG_SIZE_IN_BITS)] |= (1UL << ((index) % (UNSIGNED_LONG_SIZE_IN_BITS))); 
		} 
		else { 
			jmeno_pole[1 + (index)/(UNSIGNED_LONG_SIZE_IN_BITS)] &= ~(1UL << ((index) % (UNSIGNED_LONG_SIZE_IN_BITS))); 
		}	
	}

	inline unsigned int bitset_getbit(bitset_t jmeno_pole, unsigned long index) {
		if (index >= jmeno_pole[0]) {
			error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long) index, (unsigned long) jmeno_pole[0]);
		}
		return (jmeno_pole[1 + (index)/(UNSIGNED_LONG_SIZE_IN_BITS)] & (1UL << ((index) % (UNSIGNED_LONG_SIZE_IN_BITS))) ? (1) : (0));
	}

#endif
