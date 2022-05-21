/*
*   File: htab_struct.c
*   IJC-DU2: 2)
*   Author: Roman Janota
*	Faculty of Information Technology, Brno University of Technology
*   Date: 16. 04. 2022
*	Compiled with gcc 9.3.0
*   Brief: Definition of htab struct
*/

#ifndef HTAB_STRUCT_C
#define HTAB_STRUCT_C

#include "htab.h"

/*
*	size_t size - number of records [(key,data),next]
*	size_t array_size - size of array of pointers (number of items)
*	struct htab_item **arr_ptr - pointer to dynamically allocated array of pointers
*/

struct htab {
	size_t size;
	size_t array_size;
	struct htab_item **arr_ptr;
};

#endif