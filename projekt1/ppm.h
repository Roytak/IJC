/*
*	File: ppm.h
*	IJC-DU1: B)
*	Author: Roman Janota
*	Date: 20. 03. 2022
*	Brief: Header file for module ppm.c
*/

/*
*	Structure for storing ppm image data
*	xsize - width
*	ysize - height
*	data[] - bytes of RGB pixels
*/

struct ppm {
	unsigned xsize;
	unsigned ysize;
	char data[];
};

struct ppm * ppm_read(const char * filename);

void ppm_free(struct ppm *p);