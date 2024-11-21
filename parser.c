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
void parse(FILE *file) {
    char line[MAX_LINE_LENGTH] = {0};
    char label[MAX_LABEL_LENGTH] = {0};
    int rom_address = 0;

    while (fgets(line, sizeof(line), file)) {
        strip(line); // Remove comments and whitespace
        if (!*line) {
            continue; // Skip blank lines
        }

        if (is_Atype(line)) {
            rom_address++; // Increment for A-type instruction
        } else if (is_label(line) == 1){
      		inst_type = 'L';
      		char label[MAX_LABEL_LENGTH] = {0};
     		 strcpy(line, extract_label(line, label));
      		if (!isalpha(*label)) {
       		 exit(EXIT_FAILURE);
      }    
      		if (symtable_find(label) != NULL) {  
        	exit(EXIT_FAILURE);
      }
       //printf("%s\n", label);
       symtable_insert(label, instr_num);
       continue; 
		
        } else if (is_Ctype(line)) {
            rom_address++; // Increment for C-type instruction
        }
}


bool is_Atype(const char *line) {
    return line != NULL && line[0] == '@';
}

bool is_label(const char *line) {
    if (line == NULL) return false;
    size_t len = strlen(line);
    return len > 2 && line[0] == '(' && line[len - 1] == ')';
}

bool is_Ctype(const char *line) {
    return !is_Atype(line) && !is_label(line);
}

char *extract_label(const char *line, char* label){
  int i = 0;
  for (const char *s = line; *s; s++){
    if (*s=='(' || *s==')'){
      continue;
    }
    else{
      label[i++] = *s;
    }
  }
  return label;
}

