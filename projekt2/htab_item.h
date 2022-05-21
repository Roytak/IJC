/*
*   File: htab_item.h
*   IJC-DU2: 2)
*   Author: Roman Janota
*	Faculty of Information Technology, Brno University of Technology
*   Date: 16. 04. 2022
*	Compiled with gcc 9.3.0
*   Brief: Definition of htab_item struct
*/

#ifndef HTAB_ITEM_H
#define HTAB_ITEM_H

#include "htab.h"

/*
*	struct htab_item *pair - pointer to the next item in list
*	struct htab_pair pair -	struct that holds the key and value
*/

struct htab_item {
	struct htab_item *next;
	struct htab_pair pair;
};

#endif