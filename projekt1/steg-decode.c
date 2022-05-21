/*
*	File: steg-decode.c
*	IJC-DU1: B)
*	Author: Roman Janota
*	Date: 20. 03. 2022
*	Brief: Finds a message hidden in a ppm file's data
*/

#include "ppm.h"
#include "bitset.h"
#include "eratosthenes.h"
#include "error.h"

#define IS_ODD(num) ((num) % 2 ? 1 : 0)

void Eratosthenes(bitset_t set);

struct ppm * ppm_read(const char * filename);

void error_exit(const char *fmt, ...);

const char * usage = "Spuštění: ./steg-decode \"obrazek.ppm\"! Počet argumentů: %u\n";
const char * wrong_img_format = "Nepovedlo se přečíst obrázek.\n";

int main(int argc, char *argv[]) {
	if (argc != 2) {
		error_exit(usage, argc-1);
	}

	struct ppm * image_data_ptr = ppm_read(argv[1]);

	if (image_data_ptr == NULL) {
		error_exit(wrong_img_format);
	}

	unsigned ppm_data_size = (image_data_ptr -> xsize) * (image_data_ptr -> ysize) * 3;

	bitset_alloc(bit_array, ppm_data_size);
	Eratosthenes(bit_array);	/** Only want bytes, which indexes are prime numbers */

	char *hidden_message;
	hidden_message = calloc(ppm_data_size * sizeof(char), sizeof(char));
	if (hidden_message == NULL) {
		error_exit("Nedostatečné místo pro alokaci\n");
	}

	unsigned index = 0;
	unsigned offset = 0;
	int found_null_terminator = 0;

	/*
	*	Loop through the data
	*	If the index is a prime number
	*	Check if the char on this index is odd
	*	If true, shift 1 by offset, store it on the LSB of local array and inc offset
	*	Break when 8 continuous zero bits are found
	*/

	for (unsigned i = 29; i < ppm_data_size; i++) {
		if (bitset_getbit(bit_array, i))
			continue;

		if (IS_ODD(image_data_ptr -> data[i])) {
			hidden_message[index] += 1 << offset;
		}
		offset++;
		if (offset == CHAR_BIT) {
			if (hidden_message[index] == 0) {
				found_null_terminator = 1;
				break;
			}
			index++;
			offset = 0;
		}
	}

	if (!found_null_terminator) {
		error_exit("Obrázek neobsahuje \\0. \n");
	}

	unsigned i = 0;

	while (hidden_message[i] != 0) {
		putc(hidden_message[i], stdout);
		i++;
	}


	free(hidden_message);
	free(image_data_ptr);
	bitset_free(bit_array);
	return 0;
}