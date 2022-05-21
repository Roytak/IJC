/*
*   File: htab_erase.c
*   IJC-DU2: 2)
*   Author: Roman Janota
*	Faculty of Information Technology, Brno University of Technology
*   Date: 16. 04. 2022
*	Compiled with gcc 9.3.0
*   Brief: Delete an item in the hash table
*/

#ifndef HTAB_ERASE_C
#define HTAB_ERASE_C

#include "htab.h"
#include "htab_item.h"
#include "htab_struct.c"

bool htab_erase(htab_t * t, htab_key_t key) 
{
	size_t h;
	struct htab_item *item;
	struct htab_item *prev_item;


	h = htab_hash_function(key) % (t -> array_size);
	item = t -> arr_ptr[h];
	prev_item = item;

	if (item == NULL) {
		return false;
	}

	else if (item -> next == NULL) {
		if (!(strcmp(key, item -> pair.key))) {
			free((void *) item -> pair.key);
			free(item);
			t -> arr_ptr[h] = NULL;
			return true;
		}
		return false;
	}

	else {
		while(item != NULL) {
			if (!(strcmp(key, item -> pair.key))) {
				prev_item -> next = item -> next;
				free((void *) item -> pair.key);
				free(item);
				return true;
			}
			prev_item = item;
			item = item -> next;
		}
		return false;
	}
}

#endif