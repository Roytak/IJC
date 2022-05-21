/*
*   File: htab_clear.c
*   IJC-DU2: 2)
*   Author: Roman Janota
*	Faculty of Information Technology, Brno University of Technology
*   Date: 16. 04. 2022
*	Compiled with gcc 9.3.0
*   Brief: Empties the hash table
*/

#ifndef HTAB_CLEAR_C
#define HTAB_CLEAR_C

#include "htab.h"
#include "htab_struct.c"
#include "htab_item.h"

void htab_clear(htab_t * t)
{
	struct htab_item *item;
	struct htab_item *prev_item = NULL;

	for (size_t i = 0; i < t -> array_size; i++){	/* loop through all the pointers to pointers*/
		item = t -> arr_ptr[i];
		if (item == NULL) {		/* no need to free a null pointer*/
			continue;
		}
		if (item -> next == NULL) {		/* only a single item at this hash */
			free((void *) item -> pair.key);
			free(item);
		}
		else {
			while (item != NULL) {		/* iterate through all items at this hash and free them */
				if (prev_item != NULL) {
					free((void *) prev_item -> pair.key);
					free(prev_item);
				}
				prev_item = item;
				item = item -> next;
			}
		}
	}
	if (prev_item != NULL) {
		free((void *) prev_item -> pair.key); 	/* free the last one after exiting the loop */
		free(prev_item);
	}
	t -> size = 0;
	t -> array_size = 0;
}

#endif