/*
*	File: error.c
*	IJC-DU1: B)
*	Author: Roman Janota
*	Date: 20. 03. 2022
*	Brief: Prints error messages using variadic functions
*/

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "error.h"

/*
*	Prints a warning message to the stderr stream
*/

void warning_msg(const char *fmt, ...) {
	char * msg = "CHYBA: ";

	char * warning_message = malloc(strlen(msg) + strlen(fmt) + 1);
	if (warning_message == NULL) {
		fprintf(stderr, "Chyba při alokaci paměti ve funkci warning_msg\n");
		return;
	}

	memcpy(warning_message, msg, strlen(msg));
	memcpy(warning_message + strlen(msg), fmt, strlen(fmt));

	va_list argument_list;

	va_start(argument_list, fmt);

	vfprintf(stderr, warning_message, argument_list);
	
	va_end(argument_list);

	free(warning_message);
}

/*
*	Prints a warning message to the stderr stream and exits the program
*/

void error_exit(const char *fmt, ...) {
	char * msg = "CHYBA: ";

	char * warning_message = malloc(strlen(msg) + strlen(fmt) + 1);
	
	if (warning_message == NULL) {
		fprintf(stderr, "Chyba při alokaci paměti ve funkci error_exit\n");
		return;
	}

	memcpy(warning_message, msg, strlen(msg));
	memcpy(warning_message + strlen(msg), fmt, strlen(fmt));

	va_list argument_list;

	va_start(argument_list, fmt);

	vfprintf(stderr, warning_message, argument_list);
	
	va_end(argument_list);

	free(warning_message);
	exit(1);
}
