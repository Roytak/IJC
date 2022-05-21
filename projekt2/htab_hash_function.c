/*
*   File: htab_hash_function.c
*   IJC-DU2: 2)
*   Author: Roman Janota
*   Faculty of Information Technology, Brno University of Technology
*   Date: 16. 04. 2022
*   Compiled with gcc 9.3.0
*   Brief: Creates a hash for a string str
*/

#ifndef HTAB_HASH_FUNCTION_C
#define HTAB_HASH_FUNCTION_C
#define MULTIPLIER 65599

#include "htab.h"
#include <stdint.h>

size_t htab_hash_function(const char *str) 
{
  uint32_t h=0;     
  const unsigned char *p;
  for(p=(const unsigned char*)str; *p!='\0'; p++)
      h = MULTIPLIER*h + *p;
  return h;
}

#endif