/*
*	File: ppm.c
*	IJC-DU1: B)
*	Author: Roman Janota
*	Date: 20. 03. 2022
*	Brief: Validates and reads a ppm file
*/

#include "error.h"
#include "ppm.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#define MAX_IMAGE_RESOLUTION (8000*8000*3)	/**Any image larger than this constant will lead to an error*/
#define PPM_MAX_IMG_COLOR_VAL 255	/**Accepts only 8-bit data*/

const char * error_message = "Špatný formát obrázku ";

struct ppm * ppm_read(const char * filename) {
	FILE *fr = fopen(filename, "r");
	if (fr == NULL) {
		warning_msg("Nepodařilo se otevřít soubor %s.\n", filename);
		return NULL;
	}

	unsigned width = 0, height = 0, max_color_val = 0;
	bool hasP6 = false, has_width = false, has_height = false, has_max_color_val = false; // Define boolean variables that we will use for parsing ppm file
	int c;

	/*
	We begin parsing the file, if it doesn't look like this, we will display an error and return a NULL pointer

	"P6" <ws>+
    <xsizetxt> <ws>+ <ysizetxt> <ws>+
    "255" <ws>
    <data, 3*xsize*ysize bytes>
    <EOF>

	*/

	while (!hasP6 || !has_width || !has_height || !has_max_color_val) { 
		c = fgetc(fr);
		if (!hasP6 && c == 'P') { /** 1st symbol is P */
			if ((c = fgetc(fr)) == '6') { /** 2nd symbol is 6 */
				hasP6 = true;
				while (isspace(c = fgetc(fr)) || (c == EOF)) { 
					if (c == EOF) {
						warning_msg("%s- %s\n", error_message, filename);
						fclose(fr);
						return NULL;
					}
				}
				ungetc(c, fr);
				continue;
			}
			else {	/** 2nd symbol is not 6 */
				warning_msg("%s- %s\n", error_message, filename);
				fclose(fr);
				return NULL;
			}
		}
		if (!hasP6 && c != 'P') {	/** 1st symbol is not P */
				warning_msg("%s- %s\n", error_message, filename);
				fclose(fr);
				return NULL;
		}

		if (hasP6 && !has_width && isdigit(c)) {
			while(isdigit(c = fgetc(fr)) || (c == EOF)) {	/** Found <xsizetxt> */
				if (c == EOF) {
					warning_msg("%s- %s\n", error_message, filename);
					fclose(fr);
					return NULL;
				}	
			}
			has_width = true;
			if (isspace(c)) {		
				while (isspace((c = fgetc(fr))) || (c == EOF)) {	/** Looping through ws */
					if (c == EOF) {
						warning_msg("%s- %s\n", error_message, filename);
						fclose(fr);
						return NULL;
					}
				}
			}
			else {	/** No ws */
				warning_msg("%s- %s\n", error_message, filename);
				fclose(fr);
				return NULL;
			}
		}
		if (hasP6 && !has_width && !isdigit(c)) {	/** No <xsize> */
			warning_msg("%s- %s\n", error_message, filename);
			fclose(fr);
			return NULL;
		}

		if (hasP6 && has_width && !has_height && isdigit(c)) {
			while(isdigit(c = fgetc(fr)) || (c == EOF)) {	/** Found <ysize> */
				if (c == EOF) {
					warning_msg("%s- %s\n", error_message, filename);
					fclose(fr);
					return NULL;
				}
			}
			has_height = true;
			if (isspace(c)) {
				while (isspace((c = fgetc(fr))) || (c == EOF)) {	/** Looping through ws */
					if (c == EOF) {
						warning_msg("%s- %s\n", error_message, filename);
						fclose(fr);
						return NULL;
					}
				}
				ungetc(c, fr);
				continue;
			}
			else {	/** No ws */
				warning_msg("%s- %s\n", error_message, filename);
				fclose(fr);
				return NULL;
			}
		}
		if (hasP6 && has_width && !has_height && !isdigit(c)) {		/** No <ysize> */
			warning_msg("%s- %s\n", error_message, filename);
			fclose(fr);
			return NULL;
		}

		if (hasP6 && has_width && has_height && !has_max_color_val && isdigit(c)) {
			while(isdigit(c = fgetc(fr)) || (c == EOF)) { /** Found color value */
				if (c == EOF) {
					warning_msg("%s- %s\n", error_message, filename);
					fclose(fr);
					return NULL;
				}
			}
			has_max_color_val = true;
			if (!isspace(c)) {	/** No ws */
				warning_msg("%s- %s\n", error_message, filename);
				fclose(fr);
				return NULL;
			}
			if (isspace(c = fgetc(fr))) {
				warning_msg("%s- %s\n", error_message, filename);
				fclose(fr);
				return NULL;	
			}
		}
		if (hasP6 && has_width && has_height && !has_max_color_val && !isdigit(c)) {	/** No color value */
			warning_msg("%s- %s\n", error_message, filename);
			fclose(fr);
			return NULL;
		}
	}


	rewind(fr);		/** Move file pointer back to the beginning so we can read the values with fscanf */

	int items_read = 0;

	items_read = fscanf(fr, "P6 %u %u %u", &width, &height, &max_color_val);

	if (items_read != 3) {
		warning_msg("Couldn't read the header of %s", filename);
		return NULL;
	}

	if (max_color_val != PPM_MAX_IMG_COLOR_VAL) {
		warning_msg("Špatná maximální hodnota barevných složek (%u)! Oveřte, že je rovna %d.\n", max_color_val, PPM_MAX_IMG_COLOR_VAL);
		return NULL;
	}
	if ((width * height * 3) > MAX_IMAGE_RESOLUTION) {
		warning_msg("Přesažena maximální podporovaná velikost obrazku (%u x %u)! Maximální podporovaná velikost je 8000 x 8000.", width, height);
		return NULL;
	}
	
	struct ppm * ppm_ptr;

	unsigned long img_data_size = width * height * 3;

	ppm_ptr = malloc(sizeof(*ppm_ptr) + img_data_size);
	if (ppm_ptr == NULL) {
		warning_msg("Nepovedlo se alokovat paměť ve funkci ppm_read\n");
		return NULL;
	}

	char RGB_bytes[img_data_size];

	c = fgetc(fr); 
	unsigned long i = 0;
	while ((c = fgetc(fr)) != EOF) {
		RGB_bytes[i] = c;
		if (i > img_data_size) {
			warning_msg("%s- %s\n", error_message, filename);
			free(ppm_ptr);
			fclose(fr);
			return NULL;
		}
		i++;
	}

	ppm_ptr -> xsize = width;
	ppm_ptr -> ysize = height;
	strcpy(ppm_ptr -> data, RGB_bytes);


	fclose(fr);
	return ppm_ptr;
}

/*
* Frees a ppm struct 
*/

void ppm_free(struct ppm *p) {
	if (p != NULL) {
		free(p -> data);
		free(p);
	}
}

