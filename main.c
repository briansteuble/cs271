/****************************************
 * C-ploration 7 for CS 271
 *
 * [NAME] BRIAN STEUBLE
 * [TERM] FALL 2024
 *
 ****************************************/
#include "parser.h"
#include "symtable.h"

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s [filename]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    const char *file_name = argv[1];
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        perror("Unable to open file!");
        exit(EXIT_FAILURE);
    }
    parse(file);
    symtable_print_labels();
    fclose(file);

    return 1;
}


