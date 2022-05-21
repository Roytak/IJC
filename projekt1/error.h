/*
*	File: error.h
*	IJC-DU1: B)
*	Author: Roman Janota
*	Date: 20. 03. 2022
*	Brief: Header file for error.c
*/

/*
*	Prints a warning message to the stderr stream
*/

void warning_msg(const char *fmt, ...);

/*
*	Prints a warning message to the stderr stream and exits the program
*/

void error_exit(const char *fmt, ...);
