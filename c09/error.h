

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

#ifndef __ERROR_H__
#define __ERROR_H__


enum exitcode {
	/*
	* Error code 1 represents that given file does not exist.
	*/
	EXIT_INCORRECT_ARGUMENTS,
	EXIT_CANNOT_OPEN_FILE,
	EXIT_TOO_MANY_INSTRUCTIONS,
	EXIT_INVALID_LABEL,
	EXIT_SYMBOL_ALREADY_EXISTS,
	EXIT_INVALID_A_INSTR,
};

void exit_program(enum exitcode code, ...);

#endif // ERROR_H_INCLUDED
