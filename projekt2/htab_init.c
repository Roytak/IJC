/*
*   File: htab_init.c
*   IJC-DU2: 2)
*   Author: Roman Janota
*	Faculty of Information Technology, Brno University of Technology
*   Date: 16. 04. 2022
*	Compiled with gcc 9.3.0
*   Brief: Initializes hash table
*/

/*
	 +----------+
      | size     | // number of records [(key,data),next]
      +----------+
      | arr_size | // size of array of pointers (number of items)
      +----------+
      | arr_ptr  | // pointer to dynamically allocated array of pointers
      +----------+
        |
        V
      +---+
      |ptr|-->[(key,data),next]-->[(key,data),next]-->[(key,data),next]--|
      +---+
      |ptr|--|
      +---+
      |ptr|-->[(key,data),next]-->[(key,data),next]--|
      +---+
      |ptr|--|
      +---+

*/

#ifndef HTAB_INIT_C
#define HTAB_INIT_C

#include "htab.h"
#include "htab_struct.c"
#include "htab_item.h"

htab_t *htab_init(size_t n) 
{
	htab_t *map = malloc(sizeof(*map));
	if (map == NULL) {
		fprintf(stderr, "Memory allocation error.\n");
		return NULL;
	}

	map -> size = 0;
	map -> array_size = n;
	map -> arr_ptr = malloc(n * sizeof(struct htab_item *));
	if (map -> arr_ptr == NULL) {
		fprintf(stderr, "Memory allocation error.\n");
		return NULL;
	}
	for (size_t i = 0; i < n; i++) {
		map -> arr_ptr[i] = NULL;
	}
	return map;
}

#endif