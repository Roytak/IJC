/*
*   File: io.c
*   IJC-DU2: 2)
*   Author: Roman Janota
*	Faculty of Information Technology, Brno University of Technology
*   Date: 16. 04. 2022
*	Compiled with gcc 9.3.0
*   Brief: Reads a word from a file
*/

#ifndef IO_C
#define IO_C

#include <ctype.h>
#include <string.h>
#include <stdio.h>

/*
*	Reads a word of max length max into char *s from file f
*/

int read_word(char *s, int max, FILE *f)
{
	int c = 0, i= 0, len = 0;
	static int reached_max_len = 0;
	memset(s, 0, max);	/* Set the buffer s to 0 */
	while((c = fgetc(f)) != EOF) { 	/* Loop through file */
		if (!isspace(c)) { 	/* found word */
			len++;
			s[i++] = c;
			if (i == max - 1) {		/* Reached max length */
				s[max - 1] = '\0';
				if (reached_max_len == 0) {
					fprintf(stderr, "Word %s too long.\n", s);
					reached_max_len = 1;
				}
				return max - 1;
			}
		}
		else if(c != EOF){ 	/* found a white space char */
			if(len == 0) {
				continue;
			}
			else {
				break; 	/* end of word */
			}
		}
	}
	if (c == EOF && len == 0) {  /* found eof */
		return EOF;
	}
	s[i] = '\0';
	return len;
}

#endif