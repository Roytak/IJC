/*
*   File: htab_bucket_count.c
*   IJC-DU2: 2)
*   Author: Roman Janota
*	Faculty of Information Technology, Brno University of Technology
*   Date: 16. 04. 2022
*	Compiled with gcc 9.3.0
*   Brief: Gets the size of a bucket of hash table
*/

#ifndef HTAB_BUCKET_COUNT_C
#define HTAB_BUCKET_COUNT_C

#include "htab.h"
#include "htab_struct.c"

size_t htab_bucket_count(const htab_t * t)
{
	if (t != NULL){
		return t -> array_size;
	}

	fprintf(stderr, "Can not get the bucket size of a non existant hash table. Returned 0.\n");
	return 0;
}

#endif