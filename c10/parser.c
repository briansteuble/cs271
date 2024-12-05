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
int parse(FILE *file, instruction *instructions) {

    char line[MAX_LINE_LENGTH] = {0};

    int rom_address = 0;
    unsigned int line_num = 0;
	unsigned int instr_num = 0;

	add_predefined_symbols();
	instruction instr;

	char tmp_line[MAX_LINE_LENGTH] = {0};

    while (fgets(line, sizeof(line), file)) {
        line_num++;

        if(instr_num > MAX_INSTRUCTIONS){
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
		}
        strip(line); // Remove comments and whitespace

        if (!*line) {
            continue; // Skip blank lines
        }

        if (is_label(line)) {
            char label[MAX_LABEL_LENGTH] = {0};
            strcpy(line, extract_label(line, label));
            if (!isalpha(label[0])) {
                exit_program(EXIT_INVALID_LABEL, line_num, label);
            }
            if (symtable_find(label) != NULL) {
                exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, label);
            }
            symtable_insert(label, rom_address);
        } else if (is_Atype(line)) {
            if (!parse_A_instruction(line, &instr.instr.A_TYPE_INSTR)) {
                exit_program(EXIT_INVALID_A_INSTR, line_num, line);
            }
            instr.type = A_TYPE_INSTR;

            if (instr.instr.A_TYPE_INSTR.is_addr) {
                printf("A: %d\n", instr.instr.A_TYPE_INSTR.operand.address);
            } else {
                printf("A: %s\n", instr.instr.A_TYPE_INSTR.operand.label);
            }

            rom_address++;
        } else if (is_Ctype(line)) {

            strcpy(tmp_line, line);

            parse_C_instruction(tmp_line, &instr.instr.C_TYPE_INSTR);

            if(instr.instr.C_TYPE_INSTR.comp == COMP_INVALID) {
                exit_program(EXIT_INVALID_C_COMP, line_num, line);
            }
            else if(instr.instr.C_TYPE_INSTR.dest == DEST_INVALID) {
                exit_program(EXIT_INVALID_C_DEST, line_num, line);
            }
            else if(instr.instr.C_TYPE_INSTR.jump == JMP_INVALID) {
                exit_program(EXIT_INVALID_C_JUMP, line_num, line);
            }

            printf("C: d=%d, c=%d, j=%d\n", instr.instr.C_TYPE_INSTR.dest, instr.instr.C_TYPE_INSTR.comp, instr.instr.C_TYPE_INSTR.jump);
            instr.type = C_TYPE_INSTR;
            rom_address++;
        }

        //printf("%u: %c  %s\n", rom_address, instr_type, line);
        instructions[instr_num++] = instr;
    }
    return instr_num;
}


bool is_Atype(const char *line) {
    return line != NULL && line[0] == '@';
}

bool is_label(const char *line) {
    return ((line[0] == '(') && (line[strlen(line)-1] == ')'));
}

bool is_Ctype(const char *line) {
    return !is_Atype(line) && !is_label(line);
}

char *extract_label(const char *line, char* label){
  int i = 0;
  for (const char *s = line; *s; s++){
    if (*s =='(' || *s ==')'){
      continue;
    }
    else{
      label[i++] = *s;
    }
  }
  return label;
}

void add_predefined_symbols() {
    for(int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++){
        predefined_symbol ps = predefined_symbols[i];
        symtable_insert(ps.name, ps.address);
    }
}

bool parse_A_instruction(const char *line, a_instruction *instr){
    char *s = (char *)malloc(strlen(line));

    strcpy(s, line+1);

    char *s_end = NULL;
    long result = strtol(s, &s_end, 10);

    if(s == s_end){
        instr->operand.label = malloc(strlen(line));
        strcpy(instr->operand.label, s);
        instr->is_addr = false;
    } else if (*s_end != 0){
        return false;
    } else {
        instr->operand.address = result;
        instr->is_addr = true;
    }
    return true;
}

void parse_C_instruction(char *line, c_instruction *instr) {

    char *temp = strtok(line, ";");
    char *jump = strtok(NULL, ";");
    char *dest = strtok(temp, "=");
    char *comp = strtok(NULL, "=");

    if (comp == NULL) {
        comp = dest;
        dest = NULL;
    }

    int a;
    instr->comp = str_to_compid(comp, &a);
    instr->jump = str_to_jumpid(jump);
    instr->dest = str_to_destid(dest);
    instr->a = (a == 0) ? 0 : 1;

}
