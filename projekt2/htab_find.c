/*
*   File: htab_find.c
*   IJC-DU2: 2)
*   Author: Roman Janota
*	Faculty of Information Technology, Brno University of Technology
*   Date: 16. 04. 2022
*	Compiled with gcc 9.3.0
*   Brief: Finds the item in the hash table based on the key
*/

#ifndef HTAB_FIND_C
#define HTAB_FIND_C

#include "htab.h"
#include "htab_struct.c"
#include "htab_item.h"

/*
*	Finds the item in the hash table based on the key, if found return a pointer to it, else return null
*/

htab_pair_t *htab_find(htab_t *t, htab_key_t key) 
{
	size_t h;
	struct htab_item *item;

	h = htab_hash_function(key) % (t -> array_size);
	for (item = t -> arr_ptr[h]; item != NULL; item = item -> next) {
		if (!strcmp(key, item -> pair.key)) {
			return &(item -> pair);
		}
	}
	return NULL;
}

#endif