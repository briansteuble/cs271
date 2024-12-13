/****************************************
 * C-ploration 10 for CS 271
 *
 * [NAME] BRIAN STEUBLE
 * [TERM] FALL 2024
 *
 ****************************************/
#include "parser.h"
#include "symtable.h"
#include "error.h"
#include "hack.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_INSTRUCTION_COUNT 30000

int main(int argc, const char *argv[])
{
    if (argc != 2) {
    // incorrect number of arguments
    exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
    }
    const char *file_name = argv[1];
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
    }

    instruction *instructions = malloc(MAX_INSTRUCTION_COUNT * sizeof(instruction));

    int num_instructions = parse(file, instructions);

    //symtable_print_labels();
    fclose(file);
    assemble(argv[1], instructions, num_instructions);
    free(instructions);

    return 0;
}


