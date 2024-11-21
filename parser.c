/****************************************
 * C-ploration 7 for CS 271
 *
 * [NAME] BRIAN STEUBLE
 * [TERM] FALL 2024
 *
 ****************************************/
#include "parser.h"
#include "symtable.h"

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */
char *strip(char *s){

	char s_new[strlen(s) + 1];
	int i = 0;

	for (char *s2 = s; *s2; s2++) {
        if(*s2 == '/' && *(s2 + 1) == '/') {
            break;
        }
        else if(!isspace(*s2)) {
            s_new[i++] = *s2;
        }
	}
    s_new[i] = '\0';
    strcpy(s, s_new);

    return s;
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments.
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
void parse(FILE * file){

    char inst_type;
	char line[MAX_LINE_LENGTH] = {0};
	char label[MAX_LABEL_LENGTH] = {0};

	while (fgets(line, sizeof(line), file)) {
        strip(line);
        if(!*line) {
            continue;
        }
        if (is_Atype(line)) {
            inst_type = 'A';
        }
        else if (is_label(line)) {
            inst_type = 'L';
            extract_label(line, label);
            if (strlen(label) < sizeof(line)) {
                strcpy(line, label);
                symtable_insert(line, label);  // Assuming you want to insert the label
            } else {
                // Handle overflow or invalid label length
            }
        }
        else if (is_Ctype(line)) {
            inst_type = 'C';
        } else {
            inst_type = ' ';
        }

        //printf("%c  %s\n", inst_type, line);
	}
}
bool is_Atype(const char *line) {
    return line != NULL && line[0] == '@';
}

bool is_label(const char *line) {
    size_t len = strlen(line);
    return len > 1 && line[0] == '(' && line[len - 1] == ')';
}

bool is_Ctype(const char *line) {
    return !is_Atype(line) && !is_label(line);
}

char *extract_label(const char *line, char *label) {
    size_t len = strlen(line);
    strncpy(label, line + 1, len - 2);
    label[len - 2] = '\0';
    return label;
}

