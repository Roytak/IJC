/*
*   File: tail.c
*   IJC-DU2: 1)
*   Author: Roman Janota
*	Faculty of Information Technology, Brno University of Technology
*   Date: 16. 04. 2022
*	Compiled with gcc 9.3.0
*   Brief: Reads last n lines from a file
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_NUMBER_OF_LINES 10
#define MAX_LINE_SIZE 4095

void tail(FILE *filename, long int num_lines);

int main(int argc, char *argv[]) {
	long int lines_to_read = DEFAULT_NUMBER_OF_LINES;
	char *ptr;

	/*
	*	Parsing arguments
	*/

	if (argc == 1) {
		tail(stdin, lines_to_read);
	}
	else if (argc == 2) {
		FILE *filename = fopen(argv[1], "r");
		if (filename == NULL) {
			fprintf(stderr, "Unable to open file %s\n", argv[1]);
			return 1;
		}
		tail(filename, lines_to_read);
		fclose(filename);
	}
	else if (argc == 3) {
		if(strcmp(argv[1], "-n")) {
			fprintf(stderr, "Wrong usage\n");
			return 1;
		}
		lines_to_read = strtol(argv[2], &ptr, 10);
		if (lines_to_read <= 0) {
			fprintf(stderr, "The number of lines has to be greater than 0.\n");
			return 1;
		}
		tail(stdin, lines_to_read);
	}
	else {
		if (argc != 4) {
			fprintf(stderr, "Too many arguments.\n");
			return 1;
		}
		if(strcmp(argv[1], "-n")) {
			fprintf(stderr, "Wrong usage\n");
			return 1;
		}
		lines_to_read = strtol(argv[2], &ptr, 10);
		if (lines_to_read <= 0) {
			fprintf(stderr, "The number of lines has to be greater than 0.\n");
			return 1;
		}
		FILE *filename = fopen(argv[3], "r");
		if (filename == NULL) {
			fprintf(stderr, "Unable to open file %s\n", argv[1]);
			return 1;
		}
		tail(filename, lines_to_read);
		fclose(filename);
	}
	return 0;
}

void tail(FILE *filename, long int num_lines) {
	int i = 0, first_occurence = 1;
	int len;
	char **buffer = malloc(num_lines * sizeof(char *));	/* Allocating a cyclic buffer */
	if (buffer == NULL) {
		fprintf(stderr, "Memory allocation error\n");
		return;
	}

	for (int j = 0; j < num_lines; j++) {
		buffer[j] = malloc(MAX_LINE_SIZE * sizeof(char));
		if (buffer[j] == NULL) {
			fprintf(stderr, "Memory allocation error\n");
			return;
		}
	}

	while (fgets(buffer[i % num_lines], MAX_LINE_SIZE, filename) != NULL) { /* Adding a line to the cyclic buffer */
		len = strlen(buffer[i % num_lines]);
		if ((buffer[i % num_lines][len-1] != '\n') && first_occurence == 1 && !feof(filename)) {
			fprintf(stderr, "Line '%s' too long.\n", buffer[i % num_lines]);
			first_occurence = 0;
		}
		i++;
	}
	
	for (int j = 0; j < num_lines; j++) {
		printf("%s", buffer[i % num_lines]);
		i++;
	}

	for (int j = 0; j < num_lines; j++) {
		free(buffer[j]);
	}

	free(buffer);
}