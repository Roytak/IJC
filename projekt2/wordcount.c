/*
*   File: wordcount.c
*   IJC-DU2: 2)
*   Author: Roman Janota
*	Faculty of Information Technology, Brno University of Technology
*   Date: 16. 04. 2022
*	Compiled with gcc 9.3.0
*   Brief: Main file, initializes the hash table, reads words from stdin and prints the final result
*/

#include "htab.h"
#include "io.h"
#define INITIALIZATION_SIZE 9539	/* tested on a lot of mainly prime numbers and this one seems the fastest */
#define MAX_WORD_LENGTH 127

/*
	Prints the key and value of hash table
*/

void myprint(htab_pair_t *data)
{
	printf("%s\t%d\n", data -> key, data -> value);
}

int main()
{
	int len = 0;
	char buffer[MAX_WORD_LENGTH];
	htab_pair_t *pair = NULL; 	/* stores key and value of hash table*/
	htab_t *map = htab_init(INITIALIZATION_SIZE); 	/* initialize hash table*/
	if (map == NULL) {
		return 1;
	}

	while ((len = read_word(buffer, MAX_WORD_LENGTH - 1, stdin)) != EOF) {	/* read words from stdin */
		pair = htab_lookup_add(map, buffer);	/* look for word in hash table and add it if not found*/
		if (pair == NULL) {
			return 1;
		}
		else {
			(pair -> value)++;
		}
	}

	htab_for_each(map, myprint); /* print the keys and values */
	htab_free(map);
	return 0;
}