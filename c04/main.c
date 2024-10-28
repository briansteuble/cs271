/****************************************
 * C-ploration 4 for CS 271
 *
 * [NAME] BRIAN STEUBLE
 * [TERM] FALL 2024
 *
 ****************************************/
#include "parser.h"

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
    fclose(file);

    return 1;
}


