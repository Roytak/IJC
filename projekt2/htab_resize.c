/*
*   File: htab_resize.c
*   IJC-DU2: 2)
*   Author: Roman Janota
*	Faculty of Information Technology, Brno University of Technology
*   Date: 16. 04. 2022
*	Compiled with gcc 9.3.0
*   Brief: Resizes hash table
*/

#ifndef HTAB_RESIZE_C
#define HTAB_RESIZE_C

#include "htab.h"
#include "htab_struct.c"
#include "htab_item.h"

/*
*	Private help function for resizing
*	Appends items to the end of a list
*/
static void append_item(struct htab_item **arr_ptr, struct htab_item *item, size_t hash) 
{
	struct htab_item *iter_item = arr_ptr[hash];
	item -> next = NULL;

	if (iter_item == NULL) {
		iter_item = item;
	}

	else if (iter_item -> next == NULL) {
		iter_item -> next = item;
	}

	else {
		while(iter_item != NULL) {
			if (iter_item -> next == NULL) {
				iter_item -> next = item;
			}
			iter_item = iter_item -> next;
		}
	}
}

/*
*	Resizes and rehashes the hash table
*/

void htab_resize(htab_t *t, size_t newn)
{
	struct htab_item *item;
	struct htab_item *next_item;
	struct htab_item **new_arr_ptr;
	struct htab_item **old_arr_ptr = t -> arr_ptr; /* storing it to free it at the end*/
	size_t new_hash = 0;

	new_arr_ptr = malloc(newn * sizeof(struct htab_item *)); /* create a new array of pointers to hold the items of the resized table */
	if (new_arr_ptr == NULL) {
		return;
	}

	for (size_t i = 0; i < t -> array_size; i++) {	/* loop through all the items, rehash them and append them */
		item = t -> arr_ptr[i];
		if (item == NULL) {		
			continue;
		}

		else if (item -> next == NULL) {
			new_hash = htab_hash_function(item -> pair.key) % (newn);
			append_item(new_arr_ptr, item, new_hash);
		}

		else {
			while (item != NULL) {
				next_item = item -> next;
				new_hash = htab_hash_function(item -> pair.key) % (newn);
				append_item(new_arr_ptr, item, new_hash);
				item = next_item;
			}
		}
	}

	t -> array_size = newn;
	t -> arr_ptr = new_arr_ptr;

	free(old_arr_ptr);
}


#endif