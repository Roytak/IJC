/*
*   File: htab_size.c
*   IJC-DU2: 2)
*   Author: Roman Janota
*	Faculty of Information Technology, Brno University of Technology
*   Date: 16. 04. 2022
*	Compiled with gcc 9.3.0
*   Brief: Gets the size of hash table
*/

#ifndef HTAB_SIZE_C
#define HTAB_SIZE_C

#include "htab.h"
#include "htab_struct.c"
#include "htab_item.h"

size_t htab_size(const htab_t *t) 
{
	if (t != NULL){
		return t -> size;
	}
	fprintf(stderr, "Can not get the size of a non existant hash table. Returned 0.\n");
	return 0;
}

#endif