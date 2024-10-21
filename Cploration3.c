/****************************************
 * C-ploration 3 for CS 271
 *
 * [NAME] BRIAN STEUBLE
 * [TERM] FALL 2024
 *
 ****************************************/

 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>

 #define MAX_LINE_LENGTH 200

int main(int argc, const char *argv[])
{
        if (argc != 2) {
            printf("Usage: %s [filename]\n", argv[0]);
            exit(EXIT_FAILURE);
    }
        const char *file_name = argv[1];
        FILE *fin = fopen(file_name, "r");


        if (fin == NULL) {
        perror("Unable to open file!");
        exit(EXIT_FAILURE);

    }
        int file_len = strlen(file_name) + 6;

    char out_file[file_len];
        strcpy(out_file, file_name);
        strcat(out_file, ".echo");

    FILE *fout = fopen(out_file, "w+");

    if (fout == NULL) {
        perror("Unable to open output file!");
        fclose(fin);
        return EXIT_FAILURE;
    }


    char line[MAX_LINE_LENGTH] = {0};
    unsigned int line_num = 0;

    while(fgets(line, sizeof(line), fin)) {
        line_num++;
        printf("[%04d] %s", line_num, line);
        fprintf(fout, "%s", line);
    }

    fclose(fin);
    fclose(fout);


	return 1;
}
