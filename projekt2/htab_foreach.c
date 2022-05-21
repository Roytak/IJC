/*
*   File: htab_for_each.c
*   IJC-DU2: 2)
*   Author: Roman Janota
*	Faculty of Information Technology, Brno University of Technology
*   Date: 16. 04. 2022
*	Compiled with gcc 9.3.0
*   Brief: Calls a function on each item of the hash table
*/

#ifndef HTAB_FOREACH_C
#define HTAB_FOREACH_C

#include "htab.h"
#include "htab_struct.c"
#include "htab_item.h"

void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data))
{
	size_t i = 0;
	struct htab_item *item = NULL;

	for (i = 0; i < t -> array_size; i++) {
		item = t -> arr_ptr[i];
		while (item != NULL) {
			(*f) (&(item -> pair));
			item = item -> next;
		}
	}
}

#endif