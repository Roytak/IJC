/*
*   File: htab_lookup_add.c
*   IJC-DU2: 2)
*   Author: Roman Janota
*	Faculty of Information Technology, Brno University of Technology
*   Date: 16. 04. 2022
*	Compiled with gcc 9.3.0
*   Brief: Finds/adds the item in the hash table based on the key
*/

#ifndef HTAB_LOOKUP_ADD_C
#define HTAB_LOOKUP_ADD_C

#include "htab.h"
#include "htab_struct.c"
#include "htab_item.h"

/*
*	Looks for a item in the hash table based on the key
*	If its found return a pointer to it
*	Else create new item with this key and value set to 0
*/

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) 
{
	size_t h = 0;
	struct htab_item *item = NULL;
	struct htab_item *prev_item = NULL;
	struct htab_item *new_item = NULL;
	size_t key_len = strlen(key)+1;

	h = htab_hash_function(key) % (t -> array_size);
	item = t -> arr_ptr[h];

	if (item == NULL) {	/* First item at hash h of hash table*/
		new_item = malloc(sizeof(*new_item));	/* Allocate new item*/
		if (new_item == NULL) {
			fprintf(stderr, "Memory allocation error.\n");
			return NULL;
		}

		/*
		*	Fill it with pointer to next item, null in this case
		*	key - passed by paramater
		*	value - 0
		*/
		new_item -> next = NULL;
    	new_item -> pair.key = malloc(key_len);
   		memcpy((void *)new_item -> pair.key, key, key_len);
		new_item -> pair.value = 0;
		t -> size += 1;		/* increment size of hash table */
		t -> arr_ptr[h] = new_item;
		return &(new_item -> pair);
	}

	while(item != NULL) {	/* there is an item at hash h*/
		prev_item = item;
		if (!strcmp(key, item -> pair.key)) {
			return &(item -> pair);	/* found it */
		}
		item = item -> next;
	}
	
	/*
	*	haven't found it, creating a new one at hash h
	*/

	new_item = malloc(sizeof(*new_item));
	if (new_item == NULL) {
		fprintf(stderr, "Memory allocation error.\n");
		return NULL;
	}

	new_item -> next = NULL;
	new_item -> pair.key = malloc(key_len);
   	memcpy((void *)new_item -> pair.key, key, key_len);
	new_item -> pair.value = 0;
	prev_item -> next = new_item;
	t -> size += 1;
	if ((t -> size / t -> array_size) > AVG_LEN_MAX) {
		htab_resize(t, (t -> array_size) * 2);
	}

	return &(new_item -> pair);
}

#endif