/*
*   File: htab_free.c
*   IJC-DU2: 2)
*   Author: Roman Janota
*	Faculty of Information Technology, Brno University of Technology
*   Date: 16. 04. 2022
*	Compiled with gcc 9.3.0
*   Brief: Destroys the hash table
*/

#ifndef HTAB_FREE_C
#define HTAB_FREE_C

#include "htab.h"
#include "htab_struct.c"
#include "htab_item.h"

void htab_free(htab_t * t)
{
	htab_clear(t);
	free(t -> arr_ptr);
	free(t);
}

#endif